/** @file sequence.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   05.03.2019
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

#ifndef KCPPT_SEQUENCE_HPP
#define KCPPT_SEQUENCE_HPP

namespace kcppt {

namespace sequence {

/**
 * @brief Type container of objects of type T. Use in metaprogramming to pass
 *        the sequence around as a deductible parameter pack
 * @tparam T
 * @tparam Ts
 */
template <typename T, T...Ts>
struct [[nodiscard]] sequence {
    using value_type = T;
    constexpr static auto size = sizeof...(Ts);
};

template <typename T0, typename T1>
[[nodiscard]]
constexpr auto is_sorted (T0&& t0, T1&& t1) noexcept -> bool {
    return t0 <= t1;
}

template <typename T0, typename T1, typename...Ts>
[[nodiscard]]
constexpr auto is_sorted (T0&& t0, T1&& t1, Ts&&...ts) noexcept -> bool {
    return is_sorted(t0, t1) && is_sorted(t1, ts...);
}

template <typename T>
[[nodiscard]]
constexpr auto accumulate (T&& t) noexcept -> T {
    return t;
}

template <typename T, typename...Ts>
[[nodiscard]]
constexpr auto accumulate (T&& t, Ts&&...ts) noexcept -> T {
    return t + accumulate(ts...);
}

template <typename C, typename T>
[[nodiscard]]
constexpr auto contains (C&& c, T&& t) noexcept -> bool {
    return c == t;
}

template <typename C, typename T, typename...Ts>
[[nodiscard]]
constexpr auto contains (C&& c, T&& t, Ts&&...ts) noexcept -> bool {
    return contains(c, t) || contains(c, ts...);
}


}

}

#endif /// KCPPT_SEQUENCE_HPP
