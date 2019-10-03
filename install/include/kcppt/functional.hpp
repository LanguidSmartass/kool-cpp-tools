/** @file functional.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   24.09.2019
 * 
 * @brief  Everything to do with functors and lambdas
 *         i.e. what has operator() inside it
 * 
 */

#ifndef KCPPT_FUNCTIONAL_HPP
#define KCPPT_FUNCTIONAL_HPP

#include <utility>

namespace kcppt::functional {

/**
 * @brief Jason Turner's template that allows to inherit from lambda types
 * Source:
 * https://www.youtube.com/watch?v=W-xTpqj31mI
 * https://www.youtube.com/watch?v=3wm5QzdddYc
 * https://www.youtube.com/watch?v=QsicIaOGsI4
 *
 * @tparam Fs automatically deduced pack of types of lambdas
 *
 */
template <typename...Fs>
struct merge : public Fs... {
    
    template <
        typename...Ts,
        std::enable_if_t<sizeof...(Ts) == sizeof...(Fs)>* = nullptr
    >
    constexpr explicit merge (Ts&&...ts) noexcept :
    Fs{std::forward<Ts>(ts)}...
    {}
    
    using Fs::operator()...;
};
/**
 * @brief deduction guide for the constructor
 */
template <typename...Fs>
merge(Fs...) -> merge<std::decay_t<Fs>...>;

}

#endif /// KCPPT_FUNCTIONAL_HPP
