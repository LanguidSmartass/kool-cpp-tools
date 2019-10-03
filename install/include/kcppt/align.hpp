/** @file align.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   24.03.2019
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

#ifndef KCPPT_ALIGN_HPP
#define KCPPT_ALIGN_HPP

#include "util.hpp"

namespace kcppt::align {

template <
    auto Address,
    typename AlignmentType = std::uintptr_t,
    util::enable_if_integral_t<decltype(Address)>* = nullptr
>
[[nodiscard]]
constexpr static auto is_aligned () noexcept {
    return (Address % sizeof(AlignmentType)) == 0u;
}

template <
    auto Pointer,
    typename AlignmentType = std::uintptr_t, /// unused
    util::enable_if_pointer_t<decltype(Pointer)>* = nullptr
>
[[nodiscard]]
constexpr static auto is_aligned () noexcept {
    /// compile-time pointers are (hopefully) always aligned by the compiler
    return true;
}

template <typename AlignmentType = std::uintptr_t, typename A>
[[nodiscard]]
constexpr static auto is_aligned (
    A address, util::enable_if_integral_t<A>* = nullptr
) noexcept {
    return (address % sizeof(AlignmentType)) == 0u;
}

template <typename AlignmentType = std::uintptr_t, typename PointerType>
[[nodiscard]]
static inline auto is_aligned (
    PointerType pointer, util::enable_if_pointer_t<PointerType>* = nullptr
) noexcept {
    return (
        reinterpret_cast<std::uintptr_t>(pointer) % sizeof(AlignmentType)
    ) == 0u;
}

template <typename A>
[[nodiscard]]
constexpr static auto is_aligned (
    A address,
    std::size_t alignment = sizeof(std::uintptr_t),
    util::enable_if_integral_t<A>* = nullptr
) noexcept {
    return (address % alignment) == 0u;
}

template <typename A>
[[nodiscard]]
static inline auto is_aligned (
    A address,
    std::size_t alignment = sizeof(std::uintptr_t),
    util::enable_if_pointer_t<A>* = nullptr
) noexcept {
    return (reinterpret_cast<std::uintptr_t>(address) % alignment) == 0u;
}

template <typename A>
[[nodiscard]]
constexpr static auto align_up (
    A address,
    std::size_t alignment = sizeof(std::uintptr_t),
    util::enable_if_integral_t<A>* = nullptr
) -> A {
    if (is_aligned(address))
        return address;
    return address +
    (sizeof(std::uintptr_t) - (address % sizeof(std::uintptr_t)));
}

template <typename A>
[[nodiscard]]
constexpr static auto align_down (
    A address,
    std::size_t alignment = sizeof(std::uintptr_t),
    util::enable_if_integral_t<A>* = nullptr
) -> A {
    if (is_aligned(address))
        return address;
    return address - (address % sizeof(std::uintptr_t));
}

}

#endif /// KCPPT_ALIGN_HPP
