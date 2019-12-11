//
// Created by ivan.novoselov on 12/11/2019.
//

#ifndef KCPPT_STD_ARRAY_ND_HPP
#define KCPPT_STD_ARRAY_ND_HPP

#include <array>
#include "sequence.hpp"

namespace kcppt {

namespace std_array {

namespace impl {

template <
    typename T, std::size_t N, class SequenceContainer
>
struct nd_array_hepler;


template <
    typename T, std::size_t N,
    typename I,
    template <typename I, I...>
    class SequenceContainerTemplate,
    I DeduceFirst
>
struct nd_array_hepler<T, N, SequenceContainerTemplate<I, DeduceFirst>> {
    using type = ::std::array<T, N>;
};


template <
    typename T, std::size_t N, typename I, template <typename I, I...>
    class SequenceContainerTemplate, I DeduceFirst, I...DeduceRest
>
struct nd_array_hepler<
    T, N, SequenceContainerTemplate<I, DeduceFirst, DeduceRest...>> {
    using type = ::std::array<
        typename nd_array_hepler<
            T, N, SequenceContainerTemplate<I, DeduceRest...>>::type, N
    >;
};

}

/**
 * @brief Multidimensional POD C array.
 *        Each array will have a size of:
 *        sizeof(T) * N**D, (N**D being N in a power of D)
 *
 *        Initialized instance will have familiar C signature, like
 *        double [3][3] -- 2D plain C array of doubles,
 *
 * @tparam T -- ditto
 * @tparam N -- base size of the array [1..a lot)
 * @tparam D -- number of dimensions,  [1..a lot)
 */
template <typename T, std::size_t N, std::size_t D = 1>
using std_array_nd = typename impl::nd_array_hepler<
    T, N, sequence::make_index_sequence_t<D>
>::type;

}

}


#endif /// KCPPT_STD_ARRAY_ND_HPP
