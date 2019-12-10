/** @file traits.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   22.03.2019
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
 * @brief  
 * 
 */

#ifndef KCPPT_TRAITS_HPP
#define KCPPT_TRAITS_HPP

#include "byte.hpp"

namespace kcppt::traits {

template <typename V>
constexpr static auto is_unsigned_byte_v =
    std::is_same_v<V, byte::unsigned_byte>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_unsigned_bytes_v =
    is_unsigned_byte_v<V0> && is_unsigned_byte_v<V0> && (is_unsigned_byte_v<Vs> && ...);

template <typename V>
constexpr static auto is_signed_byte_v =
    std::is_same_v<V, byte::signed_byte>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_signed_bytes_v =
    is_signed_byte_v<V0> && is_signed_byte_v<V1> && (is_signed_byte_v<Vs> && ...);

template <typename V>
constexpr static auto is_byte_v = is_unsigned_byte_v<V> || is_signed_byte_v<V>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_bytes_v =
    is_byte_v<V0> && is_byte_v<V1> && (is_byte_v<Vs> && ...);

template <typename V>
constexpr static auto is_class_v = std::is_class_v<V> && !is_byte_v<V>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_classes_v =
    is_class_v<V0> && is_class_v<V1> && (is_class_v<Vs> && ...);

template <typename V>
constexpr static auto is_unsigned_char_v = std::is_same_v<V, unsigned char>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_unsigned_chars_v =
    is_unsigned_char_v<V0> && is_unsigned_char_v<V1> && (is_unsigned_char_v<Vs> && ...);

template <typename V>
constexpr static auto is_signed_char_v =
    std::is_same_v<V, signed char> || std::is_same_v<V, char>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_signed_chars_v =
    is_signed_char_v<V0> && is_signed_char_v<V1> && (is_signed_char_v<Vs> && ...);

template <typename V>
constexpr static auto is_char_v =
    is_unsigned_char_v<V> || is_signed_char_v<V>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_chars_v =
    is_char_v<V0> && is_char_v<V1> && (is_char_v<Vs> && ...);

template <typename V>
constexpr static auto is_bool_v = std::is_same_v<V, bool>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_bools_v =
    is_bool_v<V0> && is_bool_v<V1> && (is_bool_v<Vs> && ...);

/**
 * @brief Interpretation of what an integral types is.
 *        A char should not be considered a number, as well as a boolean.
 * @tparam V
 */
template <typename V>
constexpr static auto is_integral_v =
    (std::is_integral_v<V> && !is_char_v<V> && !is_bool_v<V>) || is_byte_v<V>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_integrals_v =
    is_integral_v<V0> && is_integral_v<V1> && (is_integral_v<Vs> && ...);

template <typename V>
constexpr static auto is_signed_v =
    (std::is_signed_v<V> && is_integral_v<V>) || is_signed_byte_v<V>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_signed_v =
    is_signed_v<V0> && is_signed_v<V1> && (is_signed_v<Vs> && ...);

template <typename V>
constexpr static auto is_unsigned_v =
    (std::is_unsigned_v<V> && is_integral_v<V>) || is_unsigned_byte_v<V>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_unsigned_v =
    is_unsigned_v<V0> && is_unsigned_v<V1> && (is_unsigned_v<Vs> && ...);

template <typename V>
constexpr static auto is_pointer_v = std::is_pointer_v<V>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_pointers_v =
    is_pointer_v<V0> && is_pointer_v<V1> && (is_pointer_v<Vs> && ...);

template <typename V>
constexpr static auto is_integral_or_pointer_v =
    is_integral_v<V> || is_pointer_v<V>;

template <typename V>
constexpr static auto is_unsigned_or_pointer_v =
    is_unsigned_v<V> || std::is_pointer_v<V>;

template <typename V>
constexpr static auto is_signed_or_pointer_v =
    is_signed_v<V> || std::is_pointer_v<V>;

template <typename V>
constexpr static auto is_floating_point_v = std::is_floating_point_v<V>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_floating_point_v =
    is_floating_point_v<V0> && is_floating_point_v<V1> && (is_floating_point_v<Vs> && ...);

template <typename V>
constexpr static auto is_function_v = std::is_function_v<V>;

template <typename V0, typename V1, typename...Vs>
constexpr static auto are_functions_v =
    is_function_v<V0> && is_function_v<V1> && (is_function_v<Vs> && ...);

////////////////////////////////////////////////////////////////////////////////
// Enable if shortcuts for primitives                                         //
////////////////////////////////////////////////////////////////////////////////

using std::enable_if_t;

template <typename T>
using enable_if_char = enable_if_t<is_char_v<T>>;

template <typename T>
using enable_if_bool = enable_if_t<is_bool_v<T>>;

template <typename T>
using enable_if_integral = enable_if_t<is_integral_v<T>>;

template <typename T>
using enable_if_byte = enable_if_t<is_byte_v<T>>;

template <typename T>
using enable_if_unsigned_byte = enable_if_t<is_unsigned_byte_v<T>>;

template <typename T>
using enable_if_signed_byte = enable_if_t<is_signed_byte_v<T>>;

template <typename T>
using enable_if_floating_point = enable_if_t<is_floating_point_v<T>>;

template <typename T>
using enable_if_signed = enable_if_t<is_signed_v<T>>;

template <typename T>
using enable_if_unsigned = enable_if_t<is_unsigned_v<T>>;

template <typename T>
using enable_if_pointer = enable_if_t<is_pointer_v<T>>;

template <typename T>
using enable_if_integral_or_pointer = enable_if_t<is_integral_or_pointer_v<T>>;

template <typename T>
using enable_if_unsigned_or_pointer = enable_if_t<is_unsigned_or_pointer_v<T>>;

template <typename T>
using enable_if_function = enable_if_t<is_function_v<T>>;

}

#endif /// KCPPT_TRAITS_HPP
