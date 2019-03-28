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

#include "cast.hpp"
#include <cinttypes>

namespace kcppt {

namespace ioreg {

namespace _implementation {
//
//template <
//    auto Address,
//    util::enable_if_integral_t<decltype(Address)>* = nullptr
//>
//constexpr static auto is_aligned () noexcept {
//    return (Address % sizeof(uintptr_t)) == 0u;
//}
//
//template <
//    auto Address,
//    util::enable_if_pointer_t<decltype(Address)>* = nullptr
//>
//constexpr static auto is_aligned () noexcept {
//    return true;
//}

template <typename A>
constexpr static auto is_aligned (
    A Address, util::enable_if_integral_t<A>* = nullptr
) noexcept {
    return (Address % sizeof(uintptr_t)) == 0u;
}

template <typename A>
constexpr static auto is_aligned (
    A Address, util::enable_if_pointer_t<A>* = nullptr
) noexcept {
    (void)Address;
    return true;
}

template <typename W, auto Address>
static inline auto dereference (std::size_t i = 0u) noexcept -> volatile W& {
    static_assert(traits::is_integral_or_pointer_v<decltype(Address)>);
    static_assert(
        is_aligned(Address),
        "Raw address is unaligned to sizeof(std::uintptr_t)"
    );
    
    return reinterpret_cast<volatile W*>(Address)[i];
}

template <typename W, auto Address>
class [[nodiscard]] accessor {
    static_assert(traits::is_integral_or_pointer_v<decltype(Address)>);
//    static_assert(Address % sizeof(W) == 0u, "Address unaligned to sizeof(W)");
public:
    constexpr accessor () noexcept = default;

public:
    [[nodiscard]]
    auto read (std::size_t i = 0u) const noexcept -> W {
        return _implementation::dereference<W, Address>(i);
    }
    
    auto write (W w, std::size_t i = 0u) const noexcept -> void {
        _implementation::dereference<W, Address>(i) = w;
    }
};

template <typename W, std::uintptr_t Address>
using unsigned_address = accessor<W, Address>;

template <typename W, std::intptr_t Address>
using signed_address = accessor<W, Address>;

template <typename W, W* Pointer>
using pointer = accessor<W, Pointer>;

}

template <typename W, class IO>
class reg_single {
    static_assert(traits::is_class_v<IO>);
    
private:
    constexpr static auto _access = IO();
    const std::size_t _i;
    
    auto _read () const noexcept -> W {
        return _access.read(_i);
    }
    
    auto _write (W w) const noexcept -> void {
        _access.write(w, _i);
    }

private:
    template<typename, class, std::size_t>
    friend class reg_bank;
    
    constexpr explicit reg_single (std::size_t i) noexcept : _i(i) {}

public:
    constexpr reg_single () noexcept : _i(0u) {}
    
public:
    /**
     * @brief Intentional implicit conversion to the underlying type W
     * @return register value in an integral conversion context
     */
    [[nodiscard]]
    operator W () const noexcept { return _read(); }
    
    [[nodiscard]]
    auto operator& (W w) const noexcept -> W {
        return _read() & w;
    }
    
    [[nodiscard]]
    auto operator| (W w) const noexcept -> W {
        return _read() | w;
    }
    
    [[nodiscard]]
    auto operator^ (W w) const noexcept -> W {
        return _read() ^ w;
    }
    
    [[nodiscard]]
    auto operator~ () const noexcept -> W {
        return ~_read();
    }
    
    [[nodiscard]]
    auto operator>> (std::size_t n) const noexcept -> W {
        return _read() >> n;
    }
    
    [[nodiscard]]
    auto operator<< (std::size_t n) const noexcept -> W {
        return _read() << n;
    }
    
    auto operator= (W w) const noexcept -> const reg_single& {
        _write(w);
        return *this;
    }
    
    auto operator&= (W w) const noexcept -> const reg_single& {
        _write(*this & w);
        return *this;
    }
    
    auto operator|= (W w) const noexcept -> const reg_single& {
        _write(*this | w);
        return *this;
    }
    
    auto operator^= (W w) const noexcept -> const reg_single& {
        _write(*this ^ w);
        return *this;
    }
    
    auto operator>>= (std::size_t n) const noexcept -> const reg_single& {
        _write(*this >> n);
        return *this;
    }
    
    auto operator<<= (std::size_t n) const noexcept -> const reg_single& {
        _write(*this << n);
        return *this;
    }
    
};

template <typename W, class IO, std::size_t BankSize = 1u>
class reg_bank {
    
    static_assert(traits::is_class_v<IO>);
    static_assert(BankSize != 0u);
    
public:
    constexpr reg_bank () noexcept = default;
    
public:
    constexpr auto size () const noexcept {
        return BankSize;
    }
    
    constexpr auto operator[] (std::size_t i) const noexcept {
        return reg_single<W, IO>{ i };
    }
};

template <typename W, std::uintptr_t Address>
using reg_single_unsigned_address =
    reg_single<W, _implementation::unsigned_address<W, Address>>;

template <typename W, std::intptr_t Address>
using reg_single_signed_address =
    reg_single<W, _implementation::signed_address<W, Address>>;

template <typename W, W* Pointer>
using reg_single_pointer = reg_single<W, _implementation::pointer<W, Pointer>>;


template <typename W, std::uintptr_t Address, std::size_t BankSize>
using reg_bank_unsigned_address =
    reg_bank<W, _implementation::unsigned_address<W, Address>, BankSize>;

template <typename W, std::intptr_t Address, std::size_t BankSize>
using reg_bank_signed_address =
    reg_bank<W, _implementation::signed_address<W, Address>, BankSize>;

template <typename W, W* Pointer, std::size_t BankSize>
using reg_bank_pointer =
    reg_bank<W, _implementation::pointer<W, Pointer>, BankSize>;


/// Shorthand notations
/// General
template <typename W, class IO>
using rs = reg_single<W, IO>;

template <typename W, class IO, std::size_t BankSize>
using rb = reg_bank<W, IO, BankSize>;

/// Specific
template <typename W, std::uintptr_t Address>
using rs_uaddr = reg_single_unsigned_address<W, Address>;

template <typename W, std::intptr_t Address>
using rs_saddr = reg_single_signed_address<W, Address>;

template <typename W, W* Pointer>
using rs_ptr = reg_single_pointer<W, Pointer>;

template <typename W, std::uintptr_t Address, std::size_t BankSize>
using rb_uaddr = reg_bank_unsigned_address<W, Address, BankSize>;

template <typename W, std::intptr_t Address, std::size_t BankSize>
using rb_saddr = reg_bank_signed_address<W, Address, BankSize>;

template <typename W, W* Pointer, std::size_t BankSize>
using rb_ptr = reg_bank_pointer<W, Pointer, BankSize>;

}

}

#endif /// KCPPT_IOREG_HPP
