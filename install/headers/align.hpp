/** @file align.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   24.03.2019
 * 
 * @brief  
 * 
 */

#ifndef KCPPT_ALIGN_HPP
#define KCPPT_ALIGN_HPP

#include "util.hpp"

namespace kcppt {

namespace align {

template <
    auto Address,
    typename AlignmentType = std::uintptr_t,
    util::enable_if_integral_t<decltype(Address)>* = nullptr
>
constexpr static auto is_aligned () noexcept {
    return (Address % sizeof(AlignmentType)) == 0u;
}

template <
    auto Pointer,
    typename AlignmentType = std::uintptr_t, /// unused
    util::enable_if_pointer_t<decltype(Pointer)>* = nullptr
>
constexpr static auto is_aligned () noexcept {
    /// compile-time pointers are (hopefully) always aligned by the compiler
    return true;
}

template <std::size_t AlignmentType = std::uintptr_t, typename A>
constexpr static auto is_aligned (
    A address, util::enable_if_integral_t<A>* = nullptr
) noexcept {
    return (address % sizeof(AlignmentType)) == 0u;
}

template <std::size_t AlignmentType = std::uintptr_t, typename PointerType>
static inline auto is_aligned (
    PointerType pointer, util::enable_if_pointer_t<PointerType>* = nullptr
) noexcept {
    return (
        reinterpret_cast<std::uintptr_t>(pointer) % sizeof(AlignmentType)
    ) == 0u;
}

template <typename A>
constexpr static auto is_aligned
    A address,
    std::size_t alignment = sizeof(std::uintptr_t),
    util::enable_if_integral_t<A>* = nullptr
) noexcept {
    return (address % alignment) == 0u;
}

template <typename A>
static inline auto is_aligned (
    A address,
    std::size_t alignment = sizeof(std::uintptr_t),
    util::enable_if_pointer_t<A>* = nullptr
) noexcept {
    return (reinterpret_cast<std::uintptr_t>(address) % alignment) == 0u;
}

}

}

#endif /// KCPPT_ALIGN_HPP
