/** @file log2.hpp
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

#ifndef KCPPT_LOG2_HPP
#define KCPPT_LOG2_HPP

#include "pow2.hpp"

#include <limits>

namespace kcppt {

namespace log2 {

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
[[nodiscard]]
constexpr auto greater_equal (T&& t) noexcept -> std::intmax_t {
    if (t == 0u)
        return std::numeric_limits<std::intmax_t>::min();
    
    auto is_pow2 = pow2::is_pow2(std::forward<T>(t));
    return bitwise::rshift_count<T, 0, -1>(std::forward<T>(t)) + !is_pow2;
}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
[[nodiscard]]
constexpr auto less_equal (T&& t) noexcept -> std::intmax_t {
    if (t == 0u)
        return std::numeric_limits<std::intmax_t>::min();
    
    return bitwise::rshift_count<T, 0, -1>(std::forward<T>(t));
}

}

}

#endif /// KCPPT_LOG2_HPP
