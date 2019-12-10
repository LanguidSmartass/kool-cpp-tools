/** @file c_array.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   12.03.2019
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
 * @brief  Metaprogramming helpers and wrappers for the plain C-array of any
 *         type. Also the templated alias c_array is much cleaner to use
 *         instead of type[size] syntax, especially when you're introducing
 *         references to the array.
 *
 *         There is not much else you can do with a plain array since it can't
 *         be copied like an object.
 *         If you need this functionality just use std::array.
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
constexpr static auto size_v = traits<C>::size;

template <typename C>
using value_type_t = typename traits<C>::value_type;

template <typename C>
using type_t = typename traits<C>::type;

}

}

#endif /// KCPPT_C_ARRAY_HPP
