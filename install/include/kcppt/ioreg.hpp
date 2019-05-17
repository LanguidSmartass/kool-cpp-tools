/** @file ioreg.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   23.03.2019
 *
 * MIT License
 *
 * Copyright (c) 2019 Ivan Novoselov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @brief An abstraction to strongly type your input/output registers for some
 *        kind of hardware.
 *
 *        reg_single represents a single register.
 *        reg_bank represents a sequence of registers, which may be functionally
 *        similar, so you can iterate over them nicely using operator[].
 *
 *        reg_single constructor has an argument that is not intended to be used
 *        in any other context other than when it is used as a return object
 *        from:
 *        auto reg_bank::operator[](std::size_t i) -> reg_single { return {i}; }
 *
 *        With this particular class you can even make your own accessors for
 *        architecture-specific (processor) registers using inline assembly.
 *        The constructor must be constexpr and eiter take no arguments or have
 *        defaults to all of them.
 *        The object may contain members.
 *        Just define your own IO class with the following signature:
 *        This is an example where 'i' won't be used, but you may do so
 *        if required.
 *
 *        class io_asm_reg {
 *        public:
 *            constexpr io_asm_reg () noexcept = default;
 *
 *            auto read (std::size_t i = 0u) const noexcept {
 *                (void)i;
 *                auto r = std::uint32_t(0u);
 *                asm volatile ("input the assembly to read into 'r'");
 *                return r;
 *            }
 *            auto write (uint32_t v, std::size_t i = 0u) const noexcept {
 *                (void)i;
 *                asm volatile ("input the assembly to write from 'w'");
 *            }
 *        };
 * 
 */

#ifndef KCPPT_IOREG_HPP
#define KCPPT_IOREG_HPP

#include <cinttypes>
#include <type_traits>

#include "align.hpp"

namespace kcppt::ioreg {

namespace _implementation {

template <auto Address, typename T = void>
using select_addressed_type_t = std::conditional_t<
    traits::is_pointer_v<decltype(Address)>,
    std::remove_pointer_t<decltype(Address)>,
    std::conditional_t<
        traits::is_integral_v<decltype(Address)> && traits::is_integral_v<T>,
        T,
        void
    >
>;

template <auto Address, typename W>
[[nodiscard]]
static inline auto dereference (std::size_t i = 0u) noexcept -> volatile W& {
    static_assert(align::is_aligned<Address, W>());
    return reinterpret_cast<volatile W*>(Address)[i];
}

template <
    auto Address,
    typename T = void
>
class [[nodiscard]] accessor {
private:
    using _addressed_type = select_addressed_type_t<Address, T>;
    static_assert(!std::is_void_v<_addressed_type>);

public:
    using type = _addressed_type;

public:
    constexpr accessor () noexcept = default;

public:
    [[nodiscard]]
    auto read (std::size_t i = 0u) const noexcept -> type {
        return _implementation::dereference<Address, type>(i);
    }
    
    auto write (type v, std::size_t i = 0u) const noexcept -> void {
        _implementation::dereference<Address, type>(i) = v;
    }
};

template <std::uintptr_t Address, typename W>
using unsigned_address = accessor<Address, W>;

template <std::intptr_t Address, typename W>
using signed_address = accessor<Address, W>;

template <auto Pointer>
using pointer = accessor<Pointer>;

}

/**
 * @brief  Wrapper class template mainly for accessing 'registers' of various
 *         hardware ip cores. This way you can get away from manually
 *         dereferencing raw addresses or using global macro expressions.
 *
 * @tparam IO a class with 1 public type named 'type' and 2 member functions
 *         'read' and 'write'.
 *         'type' must be an integral type, for example std::uint32_t
 *         Signatures of the member functions must be the following, where 'i'
 *         is a bit position with a default argument = 0:
 *         auto read (std::size_t i = 0u) const noexcept -> type;
 *         auto write (type v, std::size_t i = 0u) const noexcept -> void;
 */
template <class IO>
class reg_single {
private:
    static_assert(traits::is_class_v<IO>);
    using _io_type = typename IO::type;
    static_assert(traits::is_integral_or_pointer_v<_io_type>);
    
private:
    constexpr static auto _access = IO();
    const std::size_t _i;
    
    auto _read () const noexcept -> _io_type {
        return _access.read(_i);
    }
    
    auto _write (_io_type w) const noexcept {
        _access.write(w, _i);
    }

private:
    template<class, std::size_t>
    friend class reg_bank;
    
public:
    using type = _io_type;
    
public:
    constexpr explicit reg_single (std::size_t i = 0) noexcept : _i(i) {}
    
public:
    /**
     * @brief Intentional implicit conversion to the underlying type W
     * @return register value in an integral conversion context
     */
    [[nodiscard]]
    operator type () const noexcept { return _read(); }
    
    /**
     * @brief
     * @param w
     * @return
     */
    [[nodiscard]]
    auto operator& (type w) const noexcept -> type {
        return _read() & w;
    }
    
    /**
     * @brief
     * @param w
     * @return
     */
    [[nodiscard]]
    auto operator| (type w) const noexcept -> type {
        return _read() | w;
    }
    
    /**
     * @brief
     * @param w
     * @return
     */
    [[nodiscard]]
    auto operator^ (type w) const noexcept -> type {
        return _read() ^ w;
    }
    
    /**
     * @brief
     * @return
     */
    [[nodiscard]]
    auto operator~ () const noexcept -> type {
        return ~_read();
    }
    
    /**
     * @brief
     * @param n
     * @return
     */
    template <typename S, util::enable_if_integral_t<S>* = nullptr>
    [[nodiscard]]
    auto operator<< (S n) const noexcept -> type {
        return _read() << n;
    }
    
    /**
     * @brief
     * @param n
     * @return
     */
    template <typename S, util::enable_if_integral_t<S>* = nullptr>
    [[nodiscard]]
    auto operator>> (S n) const noexcept -> type {
        return _read() >> n;
    }
    
    /**
     * @brief
     * @param w
     * @return
     */
    auto operator= (type w) const noexcept -> const reg_single& {
        _write(w);
        return *this;
    }
    
    /**
     * @brief
     * @param w
     * @return
     */
    auto operator&= (type w) const noexcept -> const reg_single& {
        _write(*this & w);
        return *this;
    }
    
    /**
     * @brief
     * @param w
     * @return
     */
    auto operator|= (type w) const noexcept -> const reg_single& {
        _write(*this | w);
        return *this;
    }
    
    /**
     * @brief
     * @param w
     * @return
     */
    auto operator^= (type w) const noexcept -> const reg_single& {
        _write(*this ^ w);
        return *this;
    }
    
    /**
     * @brief
     * @param n
     * @return
     */
    template <typename S, util::enable_if_integral_t<S>* = nullptr>
    auto operator<<= (S n) const noexcept -> const reg_single& {
        _write(*this << n);
        return *this;
    }
    
    /**
     * @brief
     * @param n
     * @return
     */
    template <typename S, util::enable_if_integral_t<S>* = nullptr>
    auto operator>>= (S n) const noexcept -> const reg_single& {
        _write(*this >> n);
        return *this;
    }
    
};

template <class IO, std::size_t BankSize>
class reg_bank {
    static_assert(BankSize != 0u);
    
public:
    using type = typename IO::type;
    
public:
    constexpr reg_bank () noexcept = default;
    
public:
    constexpr auto size () const noexcept {
        return BankSize;
    }
    
    constexpr auto operator[] (std::size_t i) const noexcept {
        return reg_single<IO>{ i };
    }
};

template <std::uintptr_t Address, typename W>
using reg_single_unsigned_address =
    reg_single<_implementation::unsigned_address<Address, W>>;

template <std::intptr_t Address, typename W>
using reg_single_signed_address =
    reg_single<_implementation::signed_address<Address, W>>;

template <auto Pointer>
using reg_single_pointer = reg_single<_implementation::pointer<Pointer>>;


template <std::uintptr_t Address, typename W, std::size_t BankSize>
using reg_bank_unsigned_address =
    reg_bank<_implementation::unsigned_address<Address, W>, BankSize>;

template <std::intptr_t Address, typename W, std::size_t BankSize>
using reg_bank_signed_address =
    reg_bank<_implementation::signed_address<Address, W>, BankSize>;

template <auto Pointer, std::size_t BankSize, util::enable_if_pointer_t<decltype(Pointer)>* = nullptr>
using reg_bank_pointer =
    reg_bank<_implementation::pointer<Pointer>, BankSize>;


/// Shorthand notations
/// General
template <class IO>
using rs = reg_single<IO>;

template <class IO, std::size_t BankSize>
using rb = reg_bank<IO, BankSize>;

/// Specific
template <std::uintptr_t Address, typename W>
using rs_uaddr = reg_single_unsigned_address<Address, W>;

template <std::intptr_t Address, typename W>
using rs_saddr = reg_single_signed_address<Address, W>;

template <auto Pointer>
using rs_ptr = reg_single_pointer<Pointer>;

template <typename W, std::uintptr_t Address, std::size_t BankSize>
using rb_uaddr = reg_bank_unsigned_address<Address, W, BankSize>;

template <typename W, std::intptr_t Address, std::size_t BankSize>
using rb_saddr = reg_bank_signed_address<Address, W, BankSize>;

template <auto Pointer, std::size_t BankSize>
using rb_ptr = reg_bank_pointer<Pointer, BankSize>;

}

#endif /// KCPPT_IOREG_HPP
