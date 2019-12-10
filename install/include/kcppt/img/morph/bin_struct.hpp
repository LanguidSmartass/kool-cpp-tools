//
// Created by ivan.novoselov on 12/10/2019.
//

#ifndef KCPPT_IMG_MORPH_BIN_STRUCT_HPP
#define KCPPT_IMG_MORPH_BIN_STRUCT_HPP

#include "../../range.hpp"
#include "../../c_array_nd.hpp"

namespace kcppt::img::morph::bin_struct {

/**
 * @brief
 * @tparam Rank number of dimensions of the structure
 *         [1D..ND]
 * @tparam Conn (connectivity) number of neighbors set to 'true' in all directions.
 *         Elements at straight directions are set with each increment  (i)
 *         Elements on diagonals are set with each subsequent increment (i + 1)
 *         [1]
 * @tparam Nbrh number of neighbors in straight directions.
 *         Essentially determines the square side (or line) size of
 *         the basic row of elements.
 *         Zero value would mean a single element set to 'true', thus it is
 *         technically useless.
 *         This parameter can be used to avoid manual binary dilation generation
 *         of the structure on itself for achieving row sizes larger than 3.
 *         [1..inf]
 */
template <std::size_t Rank, std::size_t Conn = 1u, std::size_t Nbrh = 1u>
class binary_structure {
protected:
    static_assert(Rank >= 1u);
    static_assert(Conn >= 1u);
    static_assert(Nbrh >= 1u);
//    static_assert(nbrh <= conn && conn <= 2u * rank);
    
    constexpr static auto el_per_row = 2u * Nbrh + 1u;
    
    constexpr static auto true_conn = Conn - 1u;
    
    constexpr static auto rank_signed =
        static_cast<std::intmax_t>(Rank);
    
    constexpr static auto conn_signed =
        static_cast<std::intmax_t>(true_conn);
    
    constexpr static auto nbrh_signed =
        static_cast<std::intmax_t>(Nbrh);
    
    constexpr static auto el_per_row_signed =
        static_cast<std::intmax_t>(el_per_row);
    
    using range = range::range<std::size_t>;

    using value_type = bool;
    
    template <typename T>
    using array_1d = c_array::c_array <T, el_per_row>;
    
    template <typename T>
    using array_nd = c_array::c_array_nd <T, el_per_row, Rank>;
    
    template <typename T>
    using subscript_array_nd = c_array::c_array_nd <T, el_per_row, Rank - 1>;
    
    using bin_array_1d = array_1d <value_type>;
    
    using bin_array_nd = array_nd <value_type>;
    
    template <bool B>
    using enable_if_t = std::enable_if_t<B>;
    
    template <typename T>
    using enable_if_vt = enable_if_t<std::is_same_v<T, value_type>>;
    template <typename T>
    using enable_if_not_vt = enable_if_t<!std::is_same_v<T, value_type>>;
    
    /**
     * @brief a trick for 'operator[]'
     */
    template <std::size_t R>
    struct subscript_return_type {
        using type = subscript_array_nd<value_type>;
    };
    
    template <>
    struct subscript_return_type<1> {
        using type = value_type;
    };
    
    template <std::size_t R>
    using subscript_return_type_t = typename subscript_return_type<R>::type;
    
    using op_subscript_rt = subscript_return_type_t<Rank>;
    
    constexpr static auto make_magic_numbers () noexcept {
        auto ret = std::array<std::intmax_t, el_per_row> {};
        constexpr auto threshold = (el_per_row + 1) / 2;
        for (auto const i : range(0, threshold)) {
            ret[i] = i;
        }
        for (auto const i : range(threshold, el_per_row)) {
            ret[i] = el_per_row_signed - 1 - i;
        }
        return ret;
    }
    
    constexpr static auto make_magic_offset () noexcept {
        return (2 - rank_signed) * nbrh_signed + conn_signed;
    }
    
    constexpr static auto magic_numbers = make_magic_numbers();
    
    constexpr static auto magic_offset = make_magic_offset();
    
    constexpr static auto curr_neighbors () noexcept {
        return magic_offset;
    }
    
    template <typename...Indices>
    constexpr static auto curr_neighbors (Indices...indices) noexcept {
        return magic_offset + (... + magic_numbers[indices]);
    }
    
    template <typename...Indices>
    constexpr static auto curr_neighbors_trunc (Indices...indices) noexcept {
        constexpr auto max = el_per_row_signed / 2;
        auto ret = curr_neighbors(indices...);
        if (ret > max) {
            ret = max;
        }
        return ret;
    }
    
    /**
     * @brief
     * @param row row to handle
     * @param n number of neighbors to set as well as the center
     * @return void
     */
    template <typename T, typename...Is, enable_if_vt<T>* = nullptr>
    constexpr static auto recursive_set (array_1d<T>& row, Is...is) {
        constexpr auto row_size = kcppt::c_array::size_v<bin_array_1d>;
        auto const n = curr_neighbors_trunc(is...);
        if (n < 0) {
            return;
        }
        auto const n_set = 2 * n + 1;
        
        auto const begin = (row_size - 2 * n) / 2;
        auto const end   = (row_size + 2 * n + 1) / 2;
        for (auto const i : range(begin, end)) { row[i] = true; }
    }
    
    template <typename T, typename...Is, enable_if_not_vt<T>* = nullptr>
    constexpr static auto recursive_set (array_1d<T>& arr, Is...is) {
        auto i = 0;
        for (auto& subarr : arr) {
            recursive_set(subarr, is..., i++);
        }
    }
    
    bin_array_nd m_array;
    
public:
    constexpr binary_structure () : m_array {} {
        recursive_set(m_array);
    }
    
    constexpr auto operator[] (std::size_t i) const noexcept
    -> op_subscript_rt const& {
        return m_array[i];
    }
    
    constexpr auto operator[] (std::size_t i) noexcept
    -> op_subscript_rt& {
        return m_array[i];
    }
    
    constexpr auto size () const noexcept {
        constexpr auto full = sizeof(bin_array_nd) / sizeof(value_type);
        return full;
    }
    
    constexpr auto rank () const noexcept { return Rank; }
    
    constexpr auto order () const noexcept { return el_per_row; }
    
    constexpr auto center () const noexcept {
        auto half_order = order() / 2u;
        return half_order;
    }
    
    constexpr auto get () const noexcept -> bin_array_nd const& {
        return m_array;
    }
    
};


}

#endif /// KCPPT_IMG_MORPH_BIN_STRUCT_HPP
