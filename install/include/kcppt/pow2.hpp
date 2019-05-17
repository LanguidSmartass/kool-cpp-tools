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
#include "util.hpp"

namespace kcppt::pow2 {

/**
 * @brief Determine whether the number is a power of 2 or not
 * @tparam T deduced integral type
 * @param t value to test
 * @return true if power of 2, false otherwise
 */
template <typename T, typename = util::enable_if_integral_t<T>>
[[nodiscard]]
constexpr auto is_pow2 (T t) noexcept -> bool {
    /// all negative values are not powers of 2
    /// zero technically is a power of 2, but the exponent is negative infinity
    /// positive numbers can be powers of 2
    return (t < 0) ? false :
           (t == 0) ? true :
           (((t - 1) & t) == 0);
}

/**
 * @brief Get the next number that is a power of 2 and is greater than
 *        or equal to t
 * @tparam T deduced integral type
 * @param t original value
 * @return next greater or equal power of 2
 */
template <typename T, typename = util::enable_if_integral_t<T>>
[[nodiscard]]
constexpr auto pow2_ge (T t) noexcept -> T {
    if (is_pow2(t)) {
        return t;
    }
    return 1 << (bitwise::rshift_count<T, 1, 0>(t) + 1u);
}

/**
 * @brief Get the next number that is a power of 2 and is less than
 *        or equal to t
 * @tparam T deduced integral type
 * @param t original value
 * @return next less or equal power of 2
 */
template <typename T, typename = util::enable_if_integral_t<T>>
[[nodiscard]]
constexpr auto pow2_le (T&& t) noexcept -> T {
    if (is_pow2(t)) {
        return t;
    }
    return 1 << bitwise::rshift_count<T, 1, 0>(t);
}

}

#endif /// KCPPT_POW2_HPP
