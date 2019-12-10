/** @file debug.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   03.03.2019
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
 * @brief  Stolen from Scott Meyers' CppCon talk.
 *         Display the actual type the compiler has produced using the
 *         'incomplete type' error.
 */

#ifndef KCPPT_DEBUG_HPP
#define KCPPT_DEBUG_HPP

namespace kcppt {

namespace debug {

/**
 * @brief intentionally incomplete class
 * @tparam T any type
 */
template <typename T>
class type_debugger;

/**
 * @brief Displays a compilation error message so you can look what your
 *        resulting type T is. Use for type debugging.
 * @tparam T any type
 * @param t instance of any type
 */

template <typename T>
constexpr auto display_type_inside_incomplete_type_error (T&& t) noexcept {
    type_debugger<T> tt;
    return false;
}

}

}

#endif /// KCPPT_DEBUG_HPP
