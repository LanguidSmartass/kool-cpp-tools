//
// Created by ivan.novoselov on 12/10/2019.
//

#ifndef KCPPT_IMG_MORPH_BIN_STRUCT_HPP
#define KCPPT_IMG_MORPH_BIN_STRUCT_HPP

#include "../../range.hpp"
#include "../../c_array_nd.hpp"
#include "../../std_array_nd.hpp"

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
    
//    using range = range::range<std::size_t>;

    using value_type = bool;
    
    /// The compiler screwes the option with POD array usage,
    /// because somewhere during constexpr evaluation the innermost
    /// row decays into pointer, resulting in
    /// 'out of range, 0 <= index < 1' compiler error
    /// If std::array is used instead, each row is contained within it's own
    /// instance and does not decay to a pointer
    template <typename T, std::size_t N, std::size_t D = 1>
    using array_nd_impl = std_array::std_array_nd<T, N, D>;
//    using array_nd_impl = c_array::c_array_nd<T, N, D>;
    
    template <typename T>
    using array_1d = array_nd_impl <T, el_per_row>;
    
    template <typename T>
    using array_nd = array_nd_impl <T, el_per_row, Rank>;
    
    template <typename T>
    using subscript_array_nd = array_nd_impl <T, el_per_row, Rank - 1>;
    
    using bin_array_1d = array_1d <value_type>;
    
    using bin_array_nd = array_nd <value_type>;
    
    template <bool B>
    using enable_if_t = std::enable_if_t<B>;
    
    template <typename T>
    using values_init_terminate = enable_if_t<std::is_same_v<T, value_type>>;
    template <typename T>
    using values_init_recursive = enable_if_t<!std::is_same_v<T, value_type>>;
    
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
        for (auto const i : range::range(0, threshold)) {
            ret[i] = i;
        }
        for (auto const i : range::range(threshold, el_per_row)) {
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
    
    template <typename...Ts>
    struct debug_types;
    template <auto...Vs>
    struct debug_values;
    
    template <typename...Vs>
    constexpr static auto debug_values_f(Vs...vs) noexcept -> void;
    /**
     * @brief
     * @param row row to handle
     * @param n number of neighbors to set as well as the center
     * @return void
     */
    template <class InIt, class Fn>
    constexpr static auto for_each (InIt First, InIt Last, Fn Func) {
        while (First != Last) {
            Func(*First++);
        }
    }
    
    template <class InIt, class Size, class Fn>
    constexpr static auto for_each_n (InIt First, Size n, Fn Func) {
        auto const Last = First + n;
        while (First != Last) {
            Func(*First++);
        }
    }
    
    template <typename...Is>
    constexpr static auto values_init (bin_array_1d&& arr, Is...is) {
        constexpr auto row_size = el_per_row;
        auto n = curr_neighbors_trunc(is...);
        if (n < 0) {
            return;
        }
        auto const n_set = 2 * n + 1;

        auto const begin = (row_size - 2 * n) / 2;
        auto const end   = (row_size + 2 * n + 1) / 2;
        for (auto const i : range::range(begin, end)) {
            arr[i] = true;
        }
    }
    
//    template <typename...Is> ///, values_init_recursive<T>* = nullptr>
//    constexpr static auto values_init (bin_array_1d& arr, Is...is) {
//
//    }
    
    template <typename Container, typename...Is> ///, values_init_recursive<T>* = nullptr>
    constexpr static auto values_init (Container&& arr, Is...is) {
//        debug_types<Container>{};
//        debug_types<decltype(m_array)>{};
        auto i = 0;
        for (auto&& subarr : arr) {
            values_init(std::move(subarr), is..., i++);
        }
    }
    
    bin_array_nd m_array;
    
public:
    constexpr binary_structure () : m_array {} {
        values_init(std::move(m_array));
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
