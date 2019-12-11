//
// Created by ivan.novoselov on 12/10/2019.
//

#ifndef KCPPT_IMG_FILT_HPP
#define KCPPT_IMG_FILT_HPP

#include "../../range.hpp"
#include "../morph/bin_struct.hpp"

namespace kcppt::img::filt {


template <std::size_t Rank, std::size_t Conn = 1u, std::size_t Nbrh = 1u>
using bin_struct = morph::bin_struct::binary_structure<Rank, Conn, Nbrh>;


template <
    typename Container
    , std::size_t R, std::size_t C, std::size_t N
>
constexpr auto max (
    Container const& src
    , bin_struct<R, C, N> const& footprint
) noexcept {
    
    auto filtered = src;

    if (src.size() < footprint.order()) {

    }

    return filtered;
}


template <typename Container>
constexpr inline auto max (Container const& src, std::size_t n_neighbors = 1u) noexcept {
    auto const src_size   = std::size(src);
    
    auto filtered = src;
    
    for (auto const center : range::indices(src)) {

        auto bound_left_incl  = 0;
        auto bound_right_excl = center + (n_neighbors + 1);

        if (center > n_neighbors) {
            bound_left_incl = center - n_neighbors;
        }
    
        if (bound_right_excl > src_size) {
            bound_right_excl = src_size;
        }
        
        auto cbegin = std::cbegin(src) + bound_left_incl;
        auto cend = std::cbegin(src) + bound_right_excl;
        
        auto largest = std::max_element(cbegin, cend);
        
        filtered[center] = *largest;
    }
    
    return filtered;
}


}


#endif /// KCPPT_IMG_FILT_MAX_FILT_HPP
