/** @file log2.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   15.03.2019
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
