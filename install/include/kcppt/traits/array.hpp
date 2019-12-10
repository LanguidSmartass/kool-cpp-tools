/** @file array.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   09.11.2019
 * 
 * @brief  
 * 
 */


#ifndef KCPPT_TRAITS_ARRAY_HPP
#define KCPPT_TRAITS_ARRAY_HPP

#include "../c_array.hpp"
#include "../contiguous_array.hpp"

namespace kcppt::traits::array {

template <class C, class Dummy = C>
struct is_std_vector : public std::false_type {};

template <class C>
struct is_std_vector<
    C, std::vector < typename C::value_type,
        typename C::allocator_type>
> : public std::true_type {};

template <class C, class Dummy = C>
struct is_std_array : public std::false_type {};

template <class C>
struct is_std_array<C, std::array <typename C::value_type,C {}.size()>> :
    public std::true_type {};

template <class C, class Dummy = C>
struct is_c_array : public std::false_type {};

template <class C>
struct is_c_array<C, c_array::c_array < typename C::value_type, C {}.size()>> :
    public std::true_type {};

template <class C>
constexpr auto is_std_vector_v = is_std_vector<C>::value;
template <class C>
constexpr auto is_std_array_v = is_std_array<C>::value;
template <class C>
constexpr auto is_c_array_v = is_c_array<C>::value;

}

#endif /// KCPPT_TRAITS_ARRAY_HPP
