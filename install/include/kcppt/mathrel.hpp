/** @file mathrel.hpp
 *
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   24.03.2019
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

#ifndef KCPPT_MATHREL_HPP
#define KCPPT_MATHREL_HPP

#include "util.hpp"

#include <limits>

namespace kcppt::mathrel {

/**
 * @brief Returns absolute difference between two numbers at compile time.
 *        Singed/unsigned integral and floating point types are supported.
 *        The result is always positive.
 *        Arguments order doesn't matter.
 * @tparam T0 is either signed/unsigned integral or a floating point type
 * @tparam T1 ditto
 * @param n1 ditto
 * @param n2 ditto
 * @return absolute difference between n1 and n2, always >= 0
 */
template <typename T0, typename T1>
[[nodiscard]]
constexpr auto diff_abs (T0 n1, T1 n2) noexcept {
    if (n1 < 0) n1 *= -1;
    if (n2 < 0) n2 *= -1;
    if (n1 > n2) {
        return n1 - n2;
    }
    return n2 - n1;
}

/**
 * @brief
 * @tparam T
 * @param n0
 * @param n1
 * @param epsilon
 * @return
 */
template <typename T, util::enable_if_integral_t<T>* = nullptr>
[[nodiscard]]
constexpr auto are_equal (T n0, T n1) noexcept {
    return n0 == n1;
}

template <typename T, util::enable_if_floating_point_t<T>* = nullptr>
[[nodiscard]]
constexpr auto are_equal (T n0, T n1) noexcept {
    using eps_t = std::numeric_limits<double>;
    constexpr auto epsilon = eps_t::epsilon();
    double diff = n0 - n1;
    return (diff <= epsilon) && (-diff <= epsilon);
}

template <typename T>
[[nodiscard]]
constexpr auto is_even(T t) noexcept {
    return (t & 0b1) == 0u;
}

template <typename T>
[[nodiscard]]
constexpr auto is_odd(T t) noexcept {
    return !is_even(t);
}

}

#endif /// KCPPT_MATHREL_HPP
