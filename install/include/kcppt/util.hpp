/** @file util.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   20.03.2019
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

#ifndef KCPPT_UTIL_HPP
#define KCPPT_UTIL_HPP

#include "range.hpp"
#include "traits.hpp"

namespace kcppt {

namespace util {

/**
 * @brief Concatenate two containers that hold the same element type but that
 *        may be of different sizes.
 *        Can be used at compile time.
 *
 * @tparam Container deduced class template that takes T and Size
 * @tparam T deduced container element type
 * @tparam deduced size of the first container
 * @tparam Sz1 deduced size of the second container
 * @param lhs first container
 * @param rhs second container
 * @return new container with elements of lhs and rhs of size Sz0 + Sz1
 */
template <
    template <typename, std::size_t> class Container,
    typename T, std::size_t Sz0, std::size_t Sz1
>
[[nodiscard]]
constexpr auto operator+ (
    const Container<T, Sz0>& lhs, const Container<T, Sz1>& rhs
) noexcept {
    Container<T, Sz0 + Sz1> ret {};
    for (auto i : range::range(Sz0)) {
        ret[i] = lhs[i];
    }
    for (auto i : range::range(Sz1)) {
        ret[Sz0 + i] = rhs[i];
    }
    return ret;
}

/**
 * @brief Slice the elements from the source container and
 *        return them in a new one.
 *        Can be used at compile time.
 *
 * @tparam Begin start index
 * @tparam End end index
 * @tparam Step step (index += step)
 * @tparam Container deduced class template that takes T and Size
 * @tparam T deduced container element type
 * @tparam Size deduced size of the source container
 * @param src reference to the source container
 * @return new container with elements sliced from src
 */
template <
    auto Begin, auto End, auto Step = 1,
    template <typename, std::size_t> class Container,
    typename T, std::size_t Size
>
[[nodiscard]]
constexpr auto slice (const Container<T, Size>& src) noexcept {
    static_assert(Begin <= End);
    static_assert(End <= Size);
    
    constexpr auto rsize = (End - Begin) / Step + (End - Begin) % Step;
    Container<T, rsize> ret {};
    auto j = std::size_t(0u);
    for (auto i : range::range(Begin, End, Step)) {
        ret[j++] = src[i];
    }
    return ret;
}

template <typename V>
using enable_if_class_t =
std::enable_if_t<traits::is_class_v<V>, V>;

template <typename V>
using enable_if_integral_t =
std::enable_if_t<traits::is_integral_v<V>, V>;

template <typename V>
using enable_if_pointer_t =
    std::enable_if_t<traits::is_pointer_v<V>, V>;

template <typename V>
using enable_if_integral_or_pointer_t =
std::enable_if_t<traits::is_integral_or_pointer_v<V>, V>;

template <typename V>
using enable_if_unsigned_or_pointer_t =
std::enable_if_t<traits::is_unsigned_or_pointer_v<V>, V>;

template <typename V>
using enable_if_signed_or_pointer_t =
std::enable_if_t<traits::is_signed_or_pointer_v<V>, V>;

template <typename V>
using enable_if_not_integral_or_pointer_t =
std::enable_if_t<!traits::is_integral_or_pointer_v<V>, V>;

template <typename V>
using enable_if_char_t = std::enable_if_t<traits::is_char_v<V>, V>;

template <typename V>
using enable_if_bool_t = std::enable_if_t<traits::is_bool_v<V>, V>;

template <typename V>
using enable_if_signed_t = std::enable_if_t<traits::is_signed_v<V>, V>;

template <typename V>
using enable_if_unsigned_t = std::enable_if_t<traits::is_unsigned_v<V>, V>;

template <typename V>
using enable_if_floating_point_t =
    std::enable_if_t<traits::is_floating_point_v<V>, V>;

template <typename V>
using enable_if_function_t = std::enable_if_t<traits::is_function_v<V>, V>;


}

}

#endif /// KCPPT_UTIL_HPP
