/** @file nd_c_array.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   06.12.2019
 * 
 * @brief  
 * 
 */


#ifndef KCPPT_ND_C_ARRAY_HPP
#define KCPPT_ND_C_ARRAY_HPP

#include "c_array.hpp"
#include "sequence.hpp"

namespace kcppt {

namespace c_array {

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
    using type = kcppt::c_array::c_array<T, N>;
};


template <
    typename T, std::size_t N, typename I, template <typename I, I...>
    class SequenceContainerTemplate, I DeduceFirst, I...DeduceRest
>
struct nd_array_hepler<
    T, N, SequenceContainerTemplate<I, DeduceFirst, DeduceRest...>> {
    using type = kcppt::c_array::c_array<
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
using c_array_nd = typename impl::nd_array_hepler<
    T, N, sequence::make_index_sequence_t<D>
>::type;

}

}


#endif /// KCPPT_ND_C_ARRAY_HPP
