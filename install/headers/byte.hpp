/** @file byte.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   18.03.2019
 * 
 * @brief  A full 'byte' implementation. It's not a 'char' or 'unsigned char',
 *         won't show up in debug as ASCII.
 *         It's a fully arithmetic type that takes values [0..1 << CHAR_BIT).
 *         Promotable to signed/unsigned ints, floats and doubles.
 *
 */

#ifndef KCPPT_BYTE_HPP
#define KCPPT_BYTE_HPP

#include "util.hpp"

#include <cinttypes>
#include <type_traits>

namespace kcppt {

namespace byte {

template <bool IsSigned = true>
class alignas(1u) [[nodiscard]] byte  {
private:
    using _int_type = std::conditional_t<IsSigned, std::int8_t, std::uint8_t>;
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
    template <
        typename IntegerType,
        util::enable_if_integral_t<IntegerType>* = nullptr
    >
    // explicit(false) // wait for C++20
    constexpr byte (IntegerType i) noexcept :
        _enum_v(static_cast<_enum_type>(i)) {
        static_assert(std::is_integral_v<IntegerType>);
    }
    
public:
    template <
        typename IntegerType,
        util::enable_if_integral_t<IntegerType>* = nullptr
    >
    [[nodiscard]]
    // explicit(false) // wait for C++20
    constexpr operator IntegerType () {
        return static_cast<IntegerType>(_enum_v);
    }
    
    template <
        typename FloatType,
        util::enable_if_floating_point_t<FloatType>* = nullptr
    >
    [[nodiscard]]
    // explicit(false) // wait for C++20
    constexpr operator FloatType () {
        return static_cast<FloatType>(_to_int(_enum_v));
    }

public:
    
    template <typename IntegerType>
    constexpr auto operator+= (IntegerType i) noexcept -> byte& {
        _enum_v = _to_enum(_to_int(_enum_v) + i);
        return *this;
    }
    
    template <typename IntegerType>
    constexpr auto operator-= (IntegerType i) noexcept -> byte& {
        _enum_v = _to_enum(_to_int(_enum_v) - i);
        return *this;
    }
    
    template <typename IntegerType>
    [[nodiscard]]
    constexpr auto operator+ (IntegerType i) noexcept -> byte {
        return { _to_int(_enum_v) + i };
    }
    
    template <typename IntegerType>
    [[nodiscard]]
    constexpr auto operator- (IntegerType i) noexcept -> byte {
        return { _to_int(_enum_v) - i };
    }
    
    template <typename IntegerType>
    [[nodiscard]]
    constexpr auto operator* (IntegerType i) noexcept -> byte {
        return { _to_int(_enum_v) * i };
    }
    
    template <typename IntegerType>
    [[nodiscard]]
    constexpr auto operator/ (IntegerType i) noexcept -> byte {
        return { _to_int(_enum_v) / i };
    }
    
    template <typename IntegerType>
    [[nodiscard]]
    constexpr auto operator% (IntegerType i) noexcept -> byte {
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
