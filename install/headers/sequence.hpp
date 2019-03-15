/** @file sequence.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   05.03.2019
 * 
 * @brief  
 * 
 */

#ifndef KCPPT_SEQUENCE_HPP
#define KCPPT_SEQUENCE_HPP

namespace kcppt {

namespace sequence {

/**
 * @brief Type container of objects of type T. Use in metaprogramming to pass
 *        the sequence around as a deductible parameter pack
 * @tparam T
 * @tparam Ts
 */
template <typename T, T...Ts>
struct [[nodiscard]] sequence {
    using value_type = T;
    constexpr static auto size = sizeof...(Ts);
};

template <typename T0, typename T1>
[[nodiscard]]
constexpr auto is_sorted (T0&& t0, T1&& t1) noexcept -> bool {
    return t0 <= t1;
}

template <typename T0, typename T1, typename...Ts>
[[nodiscard]]
constexpr auto is_sorted (T0&& t0, T1&& t1, Ts&&...ts) noexcept -> bool {
    return is_sorted(t0, t1) && is_sorted(t1, ts...);
}

template <typename T>
[[nodiscard]]
constexpr auto accumulate (T&& t) noexcept -> T {
    return t;
}

template <typename T, typename...Ts>
[[nodiscard]]
constexpr auto accumulate (T&& t, Ts&&...ts) noexcept -> T {
    return t + accumulate(ts...);
}

template <typename C, typename T>
[[nodiscard]]
constexpr auto contains (C&& c, T&& t) noexcept -> bool {
    return c == t;
}

template <typename C, typename T, typename...Ts>
[[nodiscard]]
constexpr auto contains (C&& c, T&& t, Ts&&...ts) noexcept -> bool {
    return contains(c, t) || contains(c, ts...);
}


}

}

#endif /// KCPPT_SEQUENCE_HPP
