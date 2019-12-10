/** @file sequence.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   05.03.2019
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

#ifndef KCPPT_SEQUENCE_HPP
#define KCPPT_SEQUENCE_HPP

namespace kcppt {

namespace sequence {

namespace _impl {

//template <typename T, T...Ts>
//struct _select_first;

template <typename T, class SequenceContainer, T...Append>
struct _push_back;

template <typename T, class SequenceContainer, T...Prepend>
struct _push_front;

//template <typename T, class SequenceContainer, std::size_t N = 0>
//struct _peek_back;
//
//template <typename T, class SequenceContainer, std::size_t N = 0>
//struct _peek_front;
//
//template <typename T, class SequenceContainer, std::size_t N = 0>
//struct _pop_back;
//
//template <typename T, class SequenceContainer, std::size_t N = 0>
//struct _pop_front;

template <
    typename T,
    template <typename TD, TD...> class SequenceContainerTemplate,
    T...Append,
    T...DeducedSequence
>
struct _push_back<T, SequenceContainerTemplate<T, DeducedSequence...>, Append...> {
    using type = SequenceContainerTemplate<T, DeducedSequence..., Append...>;
};

template <
    typename T,
    template <typename TD, TD...> class SequenceContainerTemplate,
    T...Prepend,
    T...DeducedSequence
>
struct _push_front<T, SequenceContainerTemplate<T, DeducedSequence...>, Prepend...> {
    using type = SequenceContainerTemplate<T, Prepend..., DeducedSequence...>;
};

//template <typename T, template <typename TD, TD...> class SequenceContainerTemplate, T t, T...Ts>
//struct _select_last<T, SequenceContainerTemplate<T, t, Ts...>> {
//    using type = SequenceContainerTemplate<T, Ts...>;
//    constexpr static auto value = t;
//};

//template <typename T, class SequenceContainer, T...Ts>
//struct _select_last;
//
//template <
//    typename T,
//    template <typename TD, TD...> class SequenceContainerTemplate,
//    T TLast, T...TRest
//>
//struct _select_last<T, SequenceContainerTemplate<T, TRest...>, TLast> {
//    constexpr static auto value = TLast;
//    using type = SequenceContainerTemplate<T, TRest...>;
//};
//
//template <
//    typename T,
//    template <typename TD, TD...> class SequenceContainerTemplate,
//    T...DeducedSequence,
//
//>
//struct _peek_back<T, SequenceContainerTemplate<T, DeducedSequence...>> {
//    using type = SequenceContainerTemplate<T, DeducedSequence...>;
//    constexpr static auto value = _select_last<T, DeducedSequence...>::value;
//};
//
//template <
//    typename T,
//    template <typename TD, TD...> class SequenceContainerTemplate,
//    T...DeducedSequence
//>
//struct _pop_back<T, SequenceContainerTemplate<T, DeducedSequence...>> {
//    using type = SequenceContainerTemplate<T, DeducedSequence...>;
//    constexpr static auto value = _select_last<T, DeducedSequence...>::value;
//};
//
//template <
//    typename T,
//    template <typename TD, TD, TD...> class SequenceContainerTemplate,
//    T First,
//    T...DeducedSequence
//>
//struct _pop_front<T, SequenceContainerTemplate<T, First, DeducedSequence...>> {
//    using type = SequenceContainerTemplate<T, DeducedSequence...>;
//    constexpr static auto value = First;
//};

}
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

template <std::size_t...Ss>
using index_sequence = sequence<std::size_t, Ss...>;

namespace impl {

template <class SequenceContainer0, class SequenceContainer1>
struct merge_with_offset;

template <std::size_t...DeducedIndices0, std::size_t...DeducedIndices1>
struct merge_with_offset<
    index_sequence<DeducedIndices0...>
    , index_sequence<DeducedIndices1...>
> {
    using type = index_sequence<
        DeducedIndices0...
        , (sizeof...(DeducedIndices0) + DeducedIndices1)...
    >;
};

}

template <std::size_t N>
struct make_index_sequence {
    using type = typename impl::merge_with_offset<
        typename make_index_sequence<N/2>::type
        , typename make_index_sequence<N - N/2>::type
    >::type;
};

template <>
struct make_index_sequence<1>  {
    using type = index_sequence<0>;
};

template <>
struct make_index_sequence<0> {
    using type = index_sequence<>;
};

template <std::size_t N>
using make_index_sequence_t = typename make_index_sequence<N>::type;

template <typename T, class SequenceContainer, T Append>
using push_back = typename _impl::_push_back<T, SequenceContainer, Append>::type;

template <typename T, class SequenceContainer, T Prepend>
using push_front = typename _impl::_push_front<T, SequenceContainer, Prepend>::type;


template <typename T0, typename T1>
[[nodiscard]]
constexpr auto is_sorted (T0&& t0, T1&& t1) noexcept {
    return t0 <= t1;
}

template <typename T0, typename T1, typename...Ts>
[[nodiscard]]
constexpr auto is_sorted (T0&& t0, T1&& t1, Ts&&...ts) noexcept {
    return is_sorted(t0, t1) && is_sorted(t1, ts...);
}

template <typename T0, typename T1>
[[nodiscard]]
constexpr auto is_sorted_unique (T0&& t0, T1&& t1) noexcept {
    return t0 < t1;
}

template <typename T0, typename T1, typename...Ts>
[[nodiscard]]
constexpr auto is_sorted_unique (T0&& t0, T1&& t1, Ts&&...ts) noexcept {
    return is_sorted_unique(t0, t1) && is_sorted_unique(t1, ts...);
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
constexpr auto contains (C&& c, T&& t) noexcept {
    return c == t;
}

template <typename C, typename T, typename...Ts>
[[nodiscard]]
constexpr auto contains (C&& c, T&& t, Ts&&...ts) noexcept {
    return contains(c, t) || contains(c, ts...);
}


}

}

#endif /// KCPPT_SEQUENCE_HPP
