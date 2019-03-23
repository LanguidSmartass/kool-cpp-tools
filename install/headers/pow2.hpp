/** @file pow2.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   15.03.2019
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

#ifndef KCPPT_POW2_HPP
#define KCPPT_POW2_HPP

#include "bitwise.hpp"

#include <utility>

namespace kcppt {

namespace pow2 {

[[nodiscard]]
constexpr auto pow2 (std::size_t n) noexcept -> std::uintmax_t {
    return 1u << n;
}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
[[nodiscard]]
constexpr auto is_pow2 (T&& t) noexcept -> bool {
    /// all negative values are not powers of 2
    /// zero technically is a power of 2, but the exponent is negative infinity
    /// positive numbers can be powers of 2
    return (t < 0) ? false :
           (t == 0) ? true :
           (((t - 1) & t) == 0);
}

/**
 * @brief
 * @tparam T
 * @param t
 * @return
 */
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
[[nodiscard]]
constexpr auto greater_equal (T&& t) noexcept -> T {
    if (is_pow2(std::forward<T>(t))) {
        return t;
    }
    return t << (bitwise::rshift_count<T, 1, 0>(std::forward<T>(t)) + 1u);
}

/**
 * @brief
 * @tparam T
 * @param t
 * @return
 */
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
[[nodiscard]]
constexpr auto less_equal (T&& t) noexcept -> T {
    if (is_pow2(std::forward<T>(t))) {
        return t;
    }
    return t << bitwise::rshift_count<T, 1, 0>(std::forward<T>(t));
}

}

}

#endif /// KCPPT_POW2_HPP
