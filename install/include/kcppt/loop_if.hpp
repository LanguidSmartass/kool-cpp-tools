/** @file loop_if.hpp
 *
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   10.10.2019
 *
 * @brief embrace this monstrosity
 *
 */

#ifndef KCPPT_LOOP_IF_HPP
#define KCPPT_LOOP_IF_HPP

#include <utility>

#include "functional.hpp"

namespace kcppt::loop_if {

namespace fnc = functional;
template <typename D, typename Ex, typename R, typename...Ps>
using fsign_t = fnc::declaration::free_or_static_member::signature_t<D, Ex, R, Ps...>

template <typename FuncSigIf, typename FuncSigDo>
struct if_do {
    FuncSigIf func_if;
    FuncSigDo func_do;
    
    constexpr if_do (FuncSigIf f_if, FuncSigDo, f_do) noexcept :
    func_if { f_if }
    func_do { f_do }
    {}
    
};

}

#endif /// KCPPT_LOOP_IF_HPP
