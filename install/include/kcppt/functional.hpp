/** @file functional.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   24.09.2019
 * 
 * @brief  Everything to do with function signatures, functors and lambdas
 *         i.e. what has operator() inside it.
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

/**
 * @brief function signatures generators
 */
namespace declaration {

struct noexcept_true {
    constexpr static auto value = true;
};

struct noexcept_false {
    constexpr static auto value = false;
};

namespace free_or_static_member {

/**
 * @brief non-pointer declarator specification affects only free functions
 * and static member functions declarations,
 * since references to members do not exist in C++.
 */
namespace declarator {
struct _ptr {};
struct _ref_lv {};
struct _ref_rv {};
}

using d_p  = declarator::_ptr;
using d_lv = declarator::_ref_lv;
using d_rv = declarator::_ref_rv;

using ne_t = noexcept_true;
using ne_f = noexcept_false;

template <
    typename D,   // declarator
    typename Ex,  // exception specification
    typename R,   // return type
    typename...Ps // parameter types pack
>
struct signature {}; // empty default type

template <typename Ex, typename R, typename...Ps>
struct signature<d_p, Ex, R, Ps...> {
    using type = auto (*)(Ps...) noexcept(Ex::value) -> R;
};
template <typename Ex, typename R, typename...Ps>
struct signature<d_lv, Ex, R, Ps...> {
    using type = auto (&)(Ps...) noexcept(Ex::value) -> R;
};
template <typename Ex, typename R, typename...Ps>
struct signature<d_rv, Ex, R, Ps...> {
    using type = auto (&&)(Ps...) noexcept(Ex::value) -> R;
};

template <typename D, typename Ex, typename R, typename...Ps>
using signature_t = typename signature<D, Ex, R, Ps...>::type;

}

namespace non_static_member {

/**
 * @brief qualifier specification is allowed only in member function signature
 * declarations.
 */
namespace qualifier {
struct _none {};
struct _const {};
struct _volatile {};
struct _ref_lv {};
struct _ref_rv {};
}

using q_n  = qualifier::_none;
using q_c  = qualifier::_const;
using q_v  = qualifier::_volatile;
using q_lv = qualifier::_ref_lv;
using q_rv = qualifier::_ref_rv;

template <
    typename Qc,  // const qualifier
    typename Qv,  // volatile qualifier
    typename Qr,  // ref qualifier
    typename Ex,  // exception specification
    typename Cl,  // class of the member function
    typename R,   // return type
    typename...Ps // parameter types pack
>
struct signature {}; // empty default type

////////////////////////////////////////////////////////////////////////////////
// MEMBER FUNCTION POINTERS ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_n, q_n, q_n, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_n, q_n, q_lv, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) & noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_n, q_n, q_rv, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) && noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_c, q_n, q_n, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) const noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_n, q_v, q_n, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) volatile noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_c, q_v, q_n, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) const volatile noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_c, q_n, q_lv, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) const & noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_c, q_n, q_rv, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) const && noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_n, q_v, q_lv, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) volatile & noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_n, q_v, q_rv, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) volatile && noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_c, q_v, q_lv, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) const volatile & noexcept(Ex::value) -> R;
};
template <typename Ex, typename Cl, typename R, typename...Ps>
struct signature<q_c, q_v, q_rv, Ex, Cl, R, Ps...> {
    using type = auto (Cl::*)(Ps...) const volatile && noexcept(Ex::value) -> R;
};
////////////////////////////////////////////////////////////////////////////////
// There are no "references to members" in C++, therefore:
// no references to function pointers,
// no operators ->& and .&
// https://stackoverflow.com/questions/21952386/why-doesnt-reference-to-member-exist-in-c
// That's why there are no specializations for & and && declarators --
// such syntax just doesn't exist (as of 2019)
////////////////////////////////////////////////////////////////////////////////

template <
    typename Qc, typename Qv, typename Qr, typename Ex,
    typename Cl, typename R, typename...Ps
>
using signature_t = typename signature<Qc, Qv, Qr, Ex, Cl, R, Ps...>::type;

}

namespace shorthand {

//template <
//    typename Qc,  // const qualifier
//    typename Qv,  // volatile qualifier
//    typename Qr,  // ref qualifier
//    typename Ex,  // exception specification
//    typename Cl,
//    typename R,
//    typename...Ps
//>
//using nsmf_sign_t = non_static_member_function_signature_t<
//    Qc, Qv, Qr, Ex, Cl, R, Ps...
//>;
//
//namespace q = qualifier;
//
//using n = q::_none;
//using c = q::_const;
//using v = q::_volatile;
//using lv = q::_ref_lv;
//using rv = q::_ref_rv;
//
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_t = nsmf_sign_t<n, n, n, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_lv_t = nsmf_sign_t<n, n, lv, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_rv_t = nsmf_sign_t<n, n, rv, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_c_t = nsmf_sign_t<c, n, n, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_clv_t = nsmf_sign_t<c, n, lv, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_crv_t = nsmf_sign_t<c, n, rv, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_v_t = nsmf_sign_t<n, v, n, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_vlv_t = nsmf_sign_t<n, v, lv, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_vrv_t = nsmf_sign_t<n, v, rv, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_cv_t = nsmf_sign_t<c, v, n, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_cvlv_t = nsmf_sign_t<c, v, lv, Ex, Cl, R, Ps...>;
//template <typename Ex, typename Cl, typename R, typename...Ps>
//using nsmf_cvrv_t = nsmf_sign_t<c, v, rv, Ex, Cl, R, Ps...>;

}

}

}

#endif /// KCPPT_FUNCTIONAL_HPP
