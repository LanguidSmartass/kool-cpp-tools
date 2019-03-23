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

#include <type_traits>

namespace kcppt {

namespace traits {

template <typename V>
constexpr static auto is_class_v = std::is_class_v<V>;

template <typename V>
constexpr static auto is_unsigned_char_v = std::is_same_v<V, unsigned char>;

template <typename V>
constexpr static auto is_signed_char_v =
    std::is_same_v<V, signed char> || std::is_same_v<V, char>;

template <typename V>
constexpr static auto is_char_v =
    is_unsigned_char_v<V> || is_signed_char_v<V>;

template <typename V>
constexpr static auto is_bool_v = std::is_same_v<V, bool>;

/**
 * @brief Interpretation of what an integral types is.
 *        A char should not be considered a number, as well as a boolean.
 * @tparam V
 */
template <typename V>
constexpr static auto is_integral_v =
    std::is_integral_v<V> && !is_char_v<V> && !is_bool_v<V>;

template <typename V>
constexpr static auto is_signed_v =
    std::is_signed_v<V> && is_integral_v<V>;

template <typename V>
constexpr static auto is_unsigned_v =
    std::is_unsigned_v<V> && is_integral_v<V>;

template <typename V>
constexpr static auto is_integral_or_pointer_v =
    is_integral_v<V> || std::is_pointer_v<V>;

template <typename V>
constexpr static auto is_unsigned_or_pointer_v =
    is_unsigned_v<V> || std::is_pointer_v<V>;

template <typename V>
constexpr static auto is_signed_or_pointer_v =
    is_signed_v<V> || std::is_pointer_v<V>;

template <typename V>
constexpr static auto is_floating_point_v = std::is_floating_point_v<V>;

template <typename V>
constexpr static auto is_function_v = std::is_function_v<V>;

}

}

#endif /// KCPPT_TRAITS_HPP
