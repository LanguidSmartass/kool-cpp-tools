/** @file bitwise.hpp
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

#ifndef KCPPT_BITWISE_HPP
#define KCPPT_BITWISE_HPP

#include "traits.hpp"
#include "range.hpp"
#include "util.hpp"

#include <cinttypes>
#include <climits>
#include <limits>

namespace kcppt {

namespace bitwise {

template <typename T>
constexpr std::size_t bit_sizeof_v = sizeof(T) * CHAR_BIT;

template <typename T>
[[nodiscard]]
constexpr auto bit_sizeof (const T& t) noexcept -> std::size_t {
    return sizeof(t) * CHAR_BIT;
};

template <typename T>
[[nodiscard]]
constexpr auto set (T t) noexcept {
    return static_cast<T>((1u << bit_sizeof(t)) - 1u);
}

template <typename T>
[[nodiscard]]
constexpr auto clear (T t) noexcept -> T {
    (void)t;
    return 0;
}

template <typename T>
[[nodiscard]]
constexpr auto toggle (T t) noexcept -> T {
    return ~t;
}

template <typename T, typename B = std::size_t>
[[nodiscard]]
constexpr auto set (T t, B bp) noexcept -> T {
//    if constexpr (std::is_signed_v<B>) {
//        bit_sizeof_v<T>
//    }
    return t | (0b1u << bp);
}

template <typename T, typename B = std::size_t>
[[nodiscard]]
constexpr auto clear (T t, B bp) noexcept -> T {
    return t & toggle(0b1u << bp);
}

template <typename T, typename B = std::size_t>
[[nodiscard]]
constexpr auto toggle (T t, B bp) noexcept -> T {
    return t ^ (0b1u << bp);
}

template <typename T, typename B = std::size_t>
[[nodiscard]]
constexpr auto is_set (T t, B bp) noexcept -> T {
    return (t & (0b1u << bp)) != 0;
}

template <typename T, typename B = std::size_t>
[[nodiscard]]
constexpr auto is_clear (T t, B bp) noexcept -> T {
    return (t & (0b1u << bp)) == 0;
}

template <typename T>
[[nodiscard]]
constexpr auto mask (std::size_t nb = 0u) noexcept -> T {
    static_assert(traits::is_integral_v<T>);
    auto m = T{};
    for (auto i : range::range(nb)) {
        m |= (0b1u << i);
    }
    return m;
}

/**
 * @brief Right shift a given value 't' and increment the counter until 'UntilT'
 *        is reached
 * @tparam T deduced integral type
 * @tparam UntilT guard
 * @tparam CntStart counter start
 * @param t given value
 * @return counted value
 *
 */
template <
    typename T, T UntilT = 0, std::intmax_t CntStart = 0,
    typename = util::enable_if_integral_t<T>
>
constexpr auto rshift_count (T t) {
    auto cnt = CntStart;
    while (t > UntilT) {
        t >>= 1u;
        ++cnt;
    }
    return cnt;
};


}

}

#endif /// KCPPT_BITWISE_HPP
