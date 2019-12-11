//
// Created by ivan.novoselov on 12/11/2019.
//

#ifndef KCPPT_BITSET_HPP
#define KCPPT_BITSET_HPP

namespace kcppt::bitset {


template <std::size_t NBits, typename ElemType = std::uintmax_t>
class bitset final {
public:
    using utype       = ElemType;
    
    class reference final {
        friend bitset;
    
    private:
        utype& ref_byte;
        utype mask;
        
        constexpr reference (utype& rb, utype bi) noexcept :
            ref_byte {rb}, mask {static_cast<utype>(1u << bi)} {}
    
    public:
        constexpr operator bool () const noexcept {
            return (ref_byte & mask) != 0u;
        }
        
        constexpr auto operator== (reference const& other) noexcept {
            return bool(*this) == bool(other);
        }
        
        constexpr auto operator!= (reference const& other) noexcept {
            return !operator==(other);
        }
        
        constexpr auto operator= (reference const& ref) noexcept -> reference& {
            *this = bool(ref);
            return *this;
        }
        
        template <
            typename T, std::enable_if_t<
            std::is_integral_v<T>>* = nullptr
        >
        constexpr auto operator= (T t) noexcept -> reference& {
            if (t != 0) {
                ref_byte |= mask;
            } else {
                ref_byte &= static_cast<utype>(~mask);
            }
            return *this;
        }
        
    };

private:
    using range = range<std::size_t>;
    
    constexpr static auto n_bits = NBits;
    constexpr static auto n_bytes_per_element = sizeof(utype);
    constexpr static auto n_bits_per_elem =
        n_bytes_per_element * std::size_t {CHAR_BIT};
    
    constexpr static auto n_bits_tail_elem = n_bits % n_bits_per_elem;
    constexpr static auto n_elements_crop = n_bits / n_bits_per_elem;
    constexpr static auto n_elements_full =
        n_elements_crop + (n_bits_tail_elem != 0);
    
    constexpr static auto n_bytes_full =
        n_bytes_per_element * n_elements_full;
    
    constexpr auto nullify_last () noexcept {
        m_raw_data[n_elements_full - 1u] = 0u;
    }
    
    constexpr static auto runtime_elemsize_check (std::size_t sz) {
        if (sz <= n_bytes_full) { return; }
        throw std::length_error("Size overflow");
    }
    
    static auto runtime_bitpos_check (std::size_t bp) {
        if (bp <= n_bits) { return; }
        throw std::length_error("Bit position overflow");
    }


public:
    using container_t = c_array<utype, n_elements_full>;
    
    constexpr bitset () noexcept : m_raw_data {} { nullify_last(); }
    
    template <typename InIt>
    constexpr bitset (InIt Begin, InIt End) :
        bitset {} {
        runtime_elemsize_check(End - Begin);
        auto i = 0u;
        while (Begin != End) {
            this->operator[](i++) = static_cast<bool>(*Begin++);
        }
    }
    
    [[nodiscard]]
    constexpr auto operator[] (std::size_t const bitpos) noexcept -> reference {
        auto const idx_byte = bitpos / n_bits_per_elem;
        auto const tail_bitpos = static_cast<utype>(
            bitpos & (n_bits_per_elem - 1u)
        );
        return { m_raw_data[idx_byte], tail_bitpos };
    }
    
    [[nodiscard]]
    constexpr auto operator[] (std::size_t const bitpos) const noexcept -> bool {
        auto const idx_byte = bitpos / n_bits_per_elem;
        auto const tail_bitpos = static_cast<utype>(
            bitpos & (n_bits_per_elem - 1u)
        );
        return (m_raw_data[idx_byte] & (1u << tail_bitpos)) != 0;
    }
    
    [[nodiscard]]
    constexpr auto operator== (bitset const& other) const noexcept {
        auto i = 0u;
        for (auto const v : m_raw_data) {
            if (v != other.m_raw_data[i++])
                return false;
        }
        return true;
    }
    
    [[nodiscard]]
    constexpr auto operator!= (bitset const& other) const noexcept {
        return !operator==(other);
    }
    
    [[nodiscard]]
    constexpr auto count () const noexcept {
        constexpr auto bits_per_byte = "\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4"
                                       "\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
                                       "\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
                                       "\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
                                       "\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
                                       "\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
                                       "\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
                                       "\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
                                       "\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
                                       "\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
                                       "\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
                                       "\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
                                       "\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
                                       "\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
                                       "\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
                                       "\4\5\5\6\5\6\6\7\5\6\6\7\6\7\7\x8";
        union {
            uint8_t* byte_ptr;
            utype* utype_ptr;
        };
        utype_ptr = m_raw_data;
        auto cnt = 0u;
        for (auto const i : range(n_bytes_full)) {
            auto const j = byte_ptr[i];
            cnt += bits_per_byte[j];
        }
        return cnt;
    }
    
    [[nodiscard]]
    constexpr auto elements_size () const noexcept {
        return n_elements_full;
    }
    
    [[nodiscard]]
    constexpr auto element_bytesize () const noexcept {
        return n_bytes_per_element;
    }
    
    [[nodiscard]]
    constexpr auto size () const noexcept {
        return n_bits;
    }
    
    [[nodiscard]]
    constexpr auto all () const noexcept {
        return count() == size();
    }
    
    [[nodiscard]]
    constexpr auto any () const noexcept {
        for (auto const v : m_raw_data) { if (v) { return true; }}
        return false;
    }
    
    [[nodiscard]]
    constexpr auto none () const noexcept {
        return !any();
    }
    
    [[nodiscard]]
    auto data () noexcept -> utype* {
        return m_raw_data;
    }
    
    [[nodiscard]]
    constexpr auto array () const noexcept -> const container_t& {
        return m_raw_data;
    }
    
    [[nodiscard]]
    constexpr auto array () noexcept -> container_t& {
        return m_raw_data;
    }
    
    template <typename F = double>
    [[nodiscard]]
    constexpr auto similarity (
        bitset const& other, std::size_t bitwindow = 0
    ) const noexcept -> F {
        auto sim = std::size_t {};
        
        auto const n_set_this = count();
        auto const n_set_other = other.count();
        auto const n_div = (n_set_this >= n_set_other) ?
                           n_set_this : n_set_other;
        
        if (n_div == 0) {
            return 1.0;
        }
        
        auto const check_neighbors = [&sim, &other]
            (auto const begin, auto const end) {
            for (auto const i : range(begin, end)) {
                auto const& v = other.m_container[i];
                if (!v) {
                    continue;
                }
                ++sim;
                return true;
            }
            return false;
        };
        
        auto const begin = bitwindow;
        auto const end = n_bits - bitwindow;
        for (auto const i : range(begin, end)) {
            auto const& ut = operator[](i);
            auto const& rf = other.operator[](i);
            
            if (!ut) {
                continue;
            }
            
            if (ut == rf) {
                ++sim;
                continue;
            }
            
            auto const center = i;
            auto const b_left = center - bitwindow;
            auto const has_left = check_neighbors(b_left, center);
            if (has_left) {
                continue;
            }
            auto const b_right = center + bitwindow + 1;
            check_neighbors(center, b_right);
            
        }
        
        return static_cast<F>(sim) / static_cast<F>(n_div);
    }

private:
    container_t m_raw_data;
    
};



}

#endif //KCPPT_BITSET_HPP
