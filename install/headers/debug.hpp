/** @file debug.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   03.03.2019
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
 * @brief intentionally incomplete class, TD stands for TypeDebugging
 * @tparam T any type
 */
template <typename T>
class TD;

/**
 * @brief Displays a compilation error message so you can look what your
 *        resulting type T is. Use for metaprogramming debugging.
 * @tparam T any type
 * @param t instance of any type
 */
template <typename T>
constexpr auto type_display_on_compilation_error (const T&) noexcept -> void {
    TD<T> t;
}

}

}

#endif /// KCPPT_DEBUG_HPP
