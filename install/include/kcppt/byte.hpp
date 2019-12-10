/** @file byte.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   18.03.2019
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
 * @brief  A full 'byte' implementation. It's not a 'char' or 'unsigned char',
 *         won't show up in debug as ASCII.
 *         It's a fully arithmetic type that takes values [0..1 << CHAR_BIT).
 *         Promotable to signed/unsigned ints, floats and doubles.
 *
 */
 
#ifndef KCPPT_BYTE_HPP
#define KCPPT_BYTE_HPP

#include <cinttypes>
#include <type_traits>
#include <utility>

namespace kcppt {

namespace byte {

template <bool IsSigned = true>
class alignas(1u) [[nodiscard]] byte  {
private:
    using _int_type = std::conditional_t<IsSigned, std::int8_t, std::uint8_t>;
    using _display_type = std::conditional_t<IsSigned, int, unsigned int>;
    
    struct _enum {
        enum type : _int_type {};
    };
//    enum class _enum_type : _int_type {};
    using _enum_type = typename _enum::type;
    _enum_type _enum_v;

private:
    constexpr auto _to_int (_enum_type v) noexcept -> _int_type {
        return static_cast<_int_type>(v);
    }
    
    constexpr auto _to_enum (_int_type v) noexcept -> _enum_type {
        return static_cast<_enum_type>(v);
    }

public:
    constexpr byte () noexcept : _enum_v(static_cast<_enum_type>(0)) {}
    
    template <
        typename IntegerType,
        std::enable_if_t<std::is_integral_v<IntegerType>>* = nullptr
    >
    // explicit(false) // wait for C++20
    constexpr byte (IntegerType i) noexcept :
        _enum_v(static_cast<_enum_type>(i)) {
    }
    
    template <
        typename FloatingPointType,
        std::enable_if_t<std::is_floating_point_v<FloatingPointType>>* = nullptr
    >
    // explicit(false) // wait for C++20
    constexpr byte (FloatingPointType f) noexcept :
        _enum_v(static_cast<_enum_type>(f)) {
    }

public:
    template <
        typename IntegerType,
        std::enable_if_t<std::is_integral_v<IntegerType>>* = nullptr
    >
    [[nodiscard]]
    // explicit(false) // wait for C++20
    constexpr operator IntegerType () {
        return static_cast<IntegerType>(_enum_v);
    }
    
    template <
        typename FloatingPointType,
        std::enable_if_t<std::is_floating_point_v<FloatingPointType>>* = nullptr
    >
    [[nodiscard]]
    // explicit(false) // wait for C++20
    constexpr operator FloatingPointType () {
        return static_cast<FloatingPointType>(_to_int(_enum_v));
    }

public:
    
    template <typename T>
    constexpr auto operator+= (T i) noexcept -> byte& {
        _enum_v = _to_enum(_to_int(_enum_v) + i);
        return *this;
    }
    
    template <typename T>
    constexpr auto operator-= (T i) noexcept -> byte& {
        _enum_v = _to_enum(_to_int(_enum_v) - i);
        return *this;
    }
    
    template <typename T>
    [[nodiscard]]
    constexpr auto operator+ (T i) noexcept -> T {
        return { _to_int(_enum_v) + i };
    }
    
    template <typename T>
    [[nodiscard]]
    constexpr auto operator- (T i) noexcept -> T {
        return { _to_int(_enum_v) - i };
    }
    
    template <typename T>
    [[nodiscard]]
    constexpr auto operator* (T i) noexcept -> T {
        return { _to_int(_enum_v) * i };
    }
    
    template <typename T>
    [[nodiscard]]
    constexpr auto operator/ (T i) noexcept -> T {
        return { _to_int(_enum_v) / i };
    }
    
    template <typename T>
    [[nodiscard]]
    constexpr auto operator% (T i) noexcept -> T {
        return { _to_int(_enum_v) % i };
    }
    
    template <typename IntegerType>
    constexpr auto operator<<= (IntegerType shift) noexcept -> byte& {
        _enum_v = _to_enum(_to_int(_enum_v) << shift);
        return *this;
    }
    
    template <typename IntegerType>
    constexpr auto operator>>= (IntegerType shift) noexcept -> byte& {
        _enum_v = _to_enum(_to_int(_enum_v) >> shift);
        return *this;
    }
    
    template <typename IntegerType>
    [[nodiscard]]
    constexpr auto operator<< (IntegerType shift) noexcept -> byte {
        return { _to_int(_enum_v) << shift };
    }
    
    template <typename IntegerType>
    [[nodiscard]]
    constexpr auto operator>> (IntegerType shift) noexcept -> byte {
        return { _to_int(_enum_v) >> shift };
    }
    
    constexpr auto operator|= (byte other) noexcept -> byte& {
        _enum_v = _to_enum(_to_int(_enum_v) | _to_int(other._enum_v));
        return *this;
    }
    
    constexpr auto operator&= (byte other) noexcept -> byte& {
        _enum_v = _to_enum(_to_int(_enum_v) & _to_int(other._enum_v));
        return *this;
    }
    
    constexpr auto operator^= (byte other) noexcept -> byte& {
        _enum_v = _to_enum(_to_int(_enum_v) ^ _to_int(other._enum_v));
        return *this;
    }
    
    [[nodiscard]]
    constexpr auto operator| (byte other) noexcept -> byte {
        return { _to_int(_enum_v) | _to_int(other._enum_v)};
    }
    
    [[nodiscard]]
    constexpr auto operator& (byte other) noexcept -> byte {
        return { _to_int(_enum_v) & _to_int(other._enum_v)};
    }
    
    [[nodiscard]]
    constexpr auto operator^  (byte other) noexcept -> byte {
        return { _to_int(_enum_v) ^ _to_int(other._enum_v) };
    }
    
    [[nodiscard]]
    constexpr auto operator~  () noexcept -> byte {
        return { ~_to_int(_enum_v) };
    }
    
};

/** ARITHMETIC */
template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator+ (IntegerType i, byte<IsSigned> b) noexcept {
    return i + static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator- (IntegerType i, byte<IsSigned> b) noexcept {
    return i - static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator* (IntegerType i, byte<IsSigned> b) noexcept {
    return i * static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator/ (IntegerType i, byte<IsSigned> b) noexcept {
    return i / static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
constexpr auto operator% (IntegerType i, byte<IsSigned> b) noexcept {
    return i % static_cast<IntegerType>(b);
}

/** ARITHMETIC WITH ASSIGNMENT */

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator+= (IntegerType& i, byte<IsSigned> b)
noexcept -> IntegerType& {
    return i += static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator-= (IntegerType& i, byte<IsSigned> b)
noexcept -> IntegerType& {
    return i -= static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator*= (IntegerType& i, byte<IsSigned> b)
noexcept -> IntegerType& {
    return i *= static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator/= (IntegerType& i, byte<IsSigned> b)
noexcept -> IntegerType& {
    return i /= static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
constexpr auto operator%= (IntegerType& i, byte<IsSigned> b)
noexcept -> IntegerType& {
    return i %= static_cast<IntegerType>(b);
}

/** RELATIONAL */
template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator== (IntegerType i, byte<IsSigned> b) noexcept {
    return i == static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator== (byte<IsSigned> b, IntegerType i) noexcept {
    return i == static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator!= (IntegerType i, byte<IsSigned> b) noexcept {
    return i != static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator<= (IntegerType i, byte<IsSigned> b) noexcept {
    return i <= static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator>= (IntegerType i, byte<IsSigned> b) noexcept {
    return i >= static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator< (IntegerType i, byte<IsSigned> b) noexcept {
    return i <= static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator> (IntegerType i, byte<IsSigned> b) noexcept {
    return i > static_cast<IntegerType>(b);
}

/** BITWISE */
template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator& (IntegerType i, byte<IsSigned> b)
noexcept-> IntegerType {
    return i & static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator| (IntegerType i, byte<IsSigned> b)
noexcept-> IntegerType {
    return i | static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator^ (IntegerType i, byte<IsSigned> b)
noexcept-> IntegerType {
    return i ^ static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator<< (IntegerType i, byte<IsSigned> b)
noexcept-> IntegerType {
    return i << static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
[[nodiscard]]
static auto operator>> (IntegerType i, byte<IsSigned> b)
noexcept-> IntegerType {
    return i >> static_cast<IntegerType>(b);
}

/** BITWISE WITH ASSINMENT */
template <typename IntegerType, bool IsSigned>
static auto operator<<= (IntegerType& i, byte<IsSigned> b)
noexcept -> IntegerType& {
    return i <<= static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
static auto operator>>= (IntegerType& i, byte<IsSigned> b)
noexcept -> IntegerType& {
    return i >>= static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
constexpr auto operator&= (IntegerType& i, byte<IsSigned> b)
noexcept -> IntegerType& {
    return i &= static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
constexpr auto operator|= (IntegerType& i, byte<IsSigned> b)
noexcept -> IntegerType& {
    return i |= static_cast<IntegerType>(b);
}

template <typename IntegerType, bool IsSigned>
constexpr auto operator^= (IntegerType& i, byte<IsSigned> b)
noexcept -> IntegerType& {
    return i ^= static_cast<IntegerType>(b);
}

/** explicit aliases */
using unsigned_byte = byte<false>;

using signed_byte = byte<true>;

}

}

#endif /// KCPPT_BYTE_HPP
