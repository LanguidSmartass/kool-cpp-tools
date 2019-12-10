/** @file contiguous_array.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   09.11.2019
 * 
 * @brief  
 * 
 */


#ifndef KCPPT_CONTIGUOUS_ARRAY_HPP
#define KCPPT_CONTIGUOUS_ARRAY_HPP

#include <array>
#include <vector>

#include "c_array.hpp"

namespace kcppt::contiguous_array {

template <typename T, std::size_t Sz>
struct static_array_allocator {
    using value_type = T;
    constexpr static auto size = Sz;
};

template <typename T, typename Alloc = std::allocator <T>>
struct contiguous_array {
    using type = std::vector<T, Alloc>;
};

template <typename T, std::size_t Sz>
struct contiguous_array<T, static_array_allocator<T, Sz>> {
    using type = std::array<T, Sz>;
};

template <typename T, typename Alloc = std::allocator <T>>
using contiguous_array_t = typename contiguous_array<T, Alloc>::type;

}

#endif /// KCPPT_CONTIGUOUS_ARRAY_HPP
