/** @file c_array.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   12.03.2019
 * 
 * @brief  Metaprogramming helpers and wrappers for the plain C-array of any
 *         type. Also the templated alias c_array is much cleaner to use
 *         instead of type[size] syntax, especially when you're introducing
 *         references to the array.
 * 
 */

#ifndef KCPPT_C_ARRAY_HPP
#define KCPPT_C_ARRAY_HPP

#include <cinttypes>

namespace kcppt {

namespace c_array {

template <typename T, std::size_t Sz>
using c_array = T[Sz];

template <typename C>
struct traits;

template <typename T, std::size_t Sz>
struct traits<c_array<T, Sz>> {
    using type = c_array<T, Sz>;
    using value_type = T;
    constexpr static auto size = Sz;
};

template <typename C>
constexpr static auto size = traits<C>::size;

template <typename C>
using value_type = typename traits<C>::value_type;

template <typename C>
using type = typename traits<C>::type;

}

}

#endif /// KCPPT_ARRAY_HPP
