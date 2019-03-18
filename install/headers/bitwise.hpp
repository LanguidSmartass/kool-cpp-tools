/** @file bitwise.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   15.03.2019
 * 
 * @brief  
 * 
 */

#ifndef KCPPT_BITWISE_HPP
#define KCPPT_BITWISE_HPP

#include <cinttypes>
#include <type_traits>

namespace kcppt {

namespace bitwise {

template <typename T, T UntilT = 0, std::intmax_t CntStart = 0>
constexpr auto rshift_count = [](T&& t) {
    static_assert(std::is_integral_v<T>);
    
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
