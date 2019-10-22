/** @file regular_obj.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   22.10.2019
 * 
 * @brief  It's like a unique_ptr, but a regular_obj!
 *         I came up with this when I needed to return something that was
 *         generated inside a factory function with two lambdas,
 *         one lambda was a 'ctor', second was 'dtor' (both had captures),
 *         and I didn't want to use unique_ptr with a custom deleter.
 *
 *         So here you go, a piece of madness.
 *         I still genuinely laugh when I see this)
 *
 *         The only thing it lacks is inability to overload 'operator.', so I
 *         used '->' instead.
 *
 *         Or maybe you can use 'operator()' and return a reference
 *         (and thus use '.'), but that just defeats the purpose of less typing.
 */


#ifndef KCPPT_REGULAR_OBJ_HPP
#define KCPPT_REGULAR_OBJ_HPP

namespace kcppt {

namespace denial {

namespace v1 {
/**
 * @brief Regular object. Completely useless when used without it's main purpose
 *        -- a custom deleter functor.
 *        You can use it like a unique_ptr, but on the stack, semantics are
 *        basically the same.
 * @tparam T -- deduced underlying object type
 * @tparam D -- deduced custom deleter type
 */
template <typename T, typename D>
class regular_obj {
private:
    T _t;
    D _d = [](T&&){};

public:
    /**
     * @brief Construct 'regular_obj', quite useless I would say
     * @param t object to assign
     */
    regular_obj (T&& t) : _t { std::forward<T>(t) } {}
    /**
     * @brief Construct 'regular_obj' with a custom deleter
     * @param t object to assign
     * @param d custom deleter functor that must accept rvalue reference T&&
     *        as it's only argument
    */
    regular_obj (T&& t, D&& d) :
        _t { std::forward<T>(t) },
        _d { std::forward<D>(d) }
    {}
    
    ~regular_obj () { _d(std::move(_t)); }
    
    auto operator-> () noexcept -> T* { return &_t; }
    auto operator-> () const noexcept -> const T* { return &_t; }
};

template <typename T>
regular_obj (T&& c) -> regular_obj<T, auto (*)(T&&) -> void>;

template <typename T, typename D>
regular_obj (T&& t, D&& d) -> regular_obj<T, D>;

}

namespace v2 {

/**
 * @brief A little bit more obscure version, which accepts a custom 'creator'
 *        lambda as well, deduces T as creator's return value and destroys T with
 *        a custom deleter, if there are any
 * @tparam T
 * @tparam C
 * @tparam D
 */
template <typename T, typename C, typename D>
class regular_obj {
private:
    T _t;
    D _d = [](T&&){};

public:
    /**
     * @brief Construct 'regular_obj' with a custom constructor
     * @param c -- custom creator functor that must return the T
     */
    regular_obj (C&& c) : _t { std::forward<C>(c)() } {}
    /**
     * @brief Construct 'regular_obj' with a custom constructor and deleter
     * @param c -- custom creator functor that must return the T
     * @param d -- custom deleter functor that must accept rvalue reference T&&
     *        as it's only argument
     */
    regular_obj (C&& c, D&& d) :
        _t { std::forward<C>(c)() },
        _d { std::forward<D>(d) }
    {}
    
    ~regular_obj () { _d(std::move(_t)); }
    
    auto operator-> () noexcept -> T* { return &_t; }
    auto operator-> () const noexcept -> const T* { return &_t; }
};

template <typename C>
regular_obj (C&& c) -> regular_obj<decltype(c()), C, auto (*)(decltype(c())&&) -> void>;

template <typename C, typename D>
regular_obj (C&& c, D&& d) -> regular_obj<decltype(c()), C, D>;

}

}

}

#endif /// KCPPT_REGULAR_OBJ_HPP
