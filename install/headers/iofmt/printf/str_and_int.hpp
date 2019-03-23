/** @file str_and_int.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   20.03.2019
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

#ifndef KCPPT_IO_PRINTF_STR_AND_INT_HPP
#define KCPPT_IO_PRINTF_STR_AND_INT_HPP

#include "../common/conversion_table.hpp"
#include "../common/conversion.hpp"
#include "../../util.hpp"

#include <cstdarg>

namespace kcppt {

namespace io {

namespace printf {

namespace str_and_int {

namespace cvt = common::conversion_table;
namespace cv  = common::conversion;

namespace cvsp = cvt::specifiers;
namespace lmod = cvt::length_modifiers;

template <
    class PutcLambda,
    const PutcLambda& putc,
    std::size_t maxfmtlen = 256u
>
class printf_t {
public:
    constexpr printf_t () noexcept = default;
    
public:
    auto putchar (char c) const noexcept {
        putc(c);
    }
    
    auto printf (const char* fmt, ...) const noexcept {
        std::va_list arglist;
        va_start(arglist, fmt);
        vprintf(fmt, arglist);
        va_end(arglist);
    }
    
    auto vprintf (const char* fmt, std::va_list& arglist) const noexcept {
        auto p = fmt; // proxy pointer
        for (std::size_t i = 0u; i < maxfmtlen; ++i) {
            auto op = process_char_pointer(p, arglist, i);
            if (op == op::brk) {
                break;
            } else if (op == op::cnt) {
                continue;
            }
        }
    }

private:
    constexpr static auto _cvspecs =
        util::slice<cvsp::idx::c, cvsp::idx::u + 1u>(cvsp::values);
    constexpr static auto _lenmods =
        util::slice<lmod::idx::_hh, lmod::idx::_ll + 1u>(lmod::values);
    
    using wra = cv::out::ascii<PutcLambda, putc>;
    using wri = cv::out::integrals<PutcLambda, putc>;
    // write-out function pointer type
    using fpwrout_t = void(*)(const void*);
    
    /// row/columnin dices for the tables above
    using _row_index = cvsp::idx;
    using _col_index = lmod::idx;
    
    constexpr static auto _row_size = _cvspecs.size();
    constexpr static auto _col_size = _lenmods.size();
    
    constexpr static fpwrout_t _out_table[_row_size][_col_size] {
/**            hh,              h,        none,           l,          ll */
/**c*/  {wra::_hhc, wra::__hc, wra::___c, wra::__lc, wra::_llc},
/**s*/  {wra::_hhs, wra::__hs, wra::___s, wra::__ls, wra::_lls},
/**d*/  {wri::_hhd, wri::__hd, wri::___d, wri::__ld, wri::_lld},
/**o*/  {wri::_hho, wri::__ho, wri::___o, wri::__lo, wri::_llo},
/**x*/  {wri::_hhx, wri::__hx, wri::___x, wri::__lx, wri::_llx},
/**X*/  {wri::_hhX, wri::__hX, wri::___X, wri::__lX, wri::_llX},
/**u*/  {wri::_hhu, wri::__hu, wri::___u, wri::__lu, wri::_llu},
    };
    
//    /// table of expected sizes to read from argument list when encountered specific token
//    constexpr static const std::size_t* typesizes[conv_specs_cnt][length_mods_cnt] = {
//        ///         hh,               h,           none,              l,             ll
//        {cv::size::_hhc, cv::size::__hc, cv::size::___c, cv::size::__lc, cv::size::_llc}, // c
//        {cv::size::_hhs, cv::size::__hs, cv::size::___s, cv::size::__ls, cv::size::_lls}, // s
//        {cv::size::_hhd, cv::size::__hd, cv::size::___d, cv::size::__ld, cv::size::_lld}, // d/i
//        {cv::size::_hho, cv::size::__ho, cv::size::___o, cv::size::__lo, cv::size::_llo}, // o
//        {cv::size::_hhx, cv::size::__hx, cv::size::___x, cv::size::__lx, cv::size::_llx}, // x
//        {cv::size::_hhX, cv::size::__hX, cv::size::___X, cv::size::__lX, cv::size::_llX}, // X
//        {cv::size::_hhu, cv::size::__hu, cv::size::___u, cv::size::__lu, cv::size::_llu}, // u
//    };

private:
    [[nodiscard]]
    static auto parse_length_mod (const char* next, std::size_t& offs) noexcept
    -> std::size_t {
        auto c0 = next[0u];
        auto c1 = next[1u];
        
        ++offs;
        if ((c0 == 'h') && (c1 != 'h')) {
            return _col_index::__h;
        } else if (c1 == 'h') {
            ++offs;
            return _col_index::_hh;
        } else if ((c0 == 'l') && (c1 != 'l')) {
            return _col_index::__l;
        } else if (c1 == 'l') {
            ++offs;
            return _col_index::_ll;
        }
        --offs;
        return _col_index::___;
    }
    
    [[nodiscard]]
    static auto parse_conv_spec (const char* next, std::size_t& offs) noexcept
    -> std::size_t {
        auto c0 = next[0u];
        
        ++offs;
        if (c0 == 'c') {
            return _row_index::c;
        }else if (c0 == 's') {
            return _row_index::s;
        } else if ((c0 == 'd') || (c0 == 'i')) {
            return _row_index::d;
        } else if (c0 == 'o') {
            return _row_index::o;
        } else if (c0 == 'x') {
            return _row_index::x;
        } else if (c0 == 'X') {
            return _row_index::X;
        } else if (c0 == 'u') {
            return _row_index::u;
        }
//        else if ((c == 'f') || (c == 'F')) { /// floats are not supported (decimal notation)
//            return conv_spec::none;
//        } else if ((c == 'e') || (c == 'E')) { /// floats are not supported (scientific decimal notation)
//            return conv_spec::none;
//        } else if ((c == 'a') || (c == 'A')) { /// floats are not supported (hexadecimal notation)
//            return conv_spec::none;
//        } else if ((c == 'g') || (c == 'G')) { /// floats are not supported (decimal exponent notation)
//            return conv_spec::none;
//        } else if (c == 'n') {
//            return conv_spec::none;
//        } else if (c == 'p') {
//            return conv_spec::none;
//        }
        --offs;
        return _row_size;
    }
    
    // parse the symbol next after the first '%' (see the use in printf_light below)
    [[nodiscard]]
    static auto parse_argtok (
        const char* next, std::size_t& col_out, std::size_t& row_out
    ) noexcept -> std::size_t {
        auto offs = std::size_t(0u);
        col_out  = parse_length_mod(next, offs);
        row_out = parse_conv_spec(&next[offs], offs);
        return offs;
    }

private:
    template <typename T>
    [[nodiscard]]
    static auto process_va_list_helper (
        void* pbigstorage, std::va_list& arglist
    ) noexcept -> std::size_t {
        *reinterpret_cast<T*>(pbigstorage) = va_arg(arglist, T);
        return sizeof(T);
    }
    // Big and dumb function that selects a proper type to pass to va_arg
    //
    // pbigmemz ('z' intentional for funziez) pointer must point to an allocated memory region
    // of a sufficient size for any possible native data type which probably is a 'long double'
    // Alternatively you can allocate an array of bytes of a size that is guaranteed to hold the largest native
    // data type in C++.
    //
    // I really don't see any other pretty way out of this problem, since there is no way of
    // creating a variable of some arbitrary native type at runtime.
    // I could possibly create some virtual wrappers around the natives,
    // maybe
    static auto process_va_list (
        void* pbigmemz, std::va_list& arglist, std::size_t row, std::size_t col
    ) noexcept -> std::size_t {
        using ir = _row_index;
        using ic = _col_index;
        
        if ((row == ir::c) && (col == ic::___)) { // no modifiers for chars
            return process_va_list_helper<int>(pbigmemz, arglist); // char is promoted to int when passed to va_list
        } else if ((row == ir::s) && (col == ic::___)) { // no modifiers for strings
            return process_va_list_helper<const char*>(pbigmemz, arglist);
        } else if (row == ir::d) {
            // signed char, short are promoted to int when passed to va_list
            if ((col == ic::_hh) || (col == ic::__h)) {
                return process_va_list_helper<int>(pbigmemz, arglist);
            } else if (col == ic::___) {
                return process_va_list_helper<int>(pbigmemz, arglist);
            } else if (col == ic::__l) {
                return process_va_list_helper<long>(pbigmemz, arglist);
            } else if (col == ic::_ll) {
                return process_va_list_helper<long long>(pbigmemz, arglist);
            }
        } else if ((row == ir::o) || (row == ir::x) || (row == ir::X) || (row == ir::u)) {
            // unsigned char, unsigned short are promoted to int when passed to va_list
            if ((col == ic::_hh) || (col == ic::__h)) {
                return process_va_list_helper<int>(pbigmemz, arglist);
            } else if (col == ic::___) {
                return process_va_list_helper<unsigned int>(pbigmemz, arglist);
            } else if (col == ic::__l) {
                return process_va_list_helper<unsigned long>(pbigmemz, arglist);
            } else if (col == ic::_ll) {
                return process_va_list_helper<unsigned long long>(pbigmemz, arglist);
            }
        }

        return 0u;
    }

private:
    enum class op : std::uint8_t {
        brk, cnt, nop
    };
    
    [[nodiscard]]
    static auto process_char_pointer (
        const char*& p, std::va_list& arglist, std::size_t& i
    ) noexcept -> op {
        auto c0 = p[i];
        if (c0 == '\0') {
            return op::brk; ///< break
        } else if (c0 == '%') {
            if (i + 1u >= maxfmtlen)
                return op::brk; ///< break
            if (p[i + 1u] == '\0')
                return op::brk; ///< break
            
            auto col = _col_size;
            auto row = _row_size;
            auto j    = std::size_t(i + 1u); // save i + 1u
            
            i += parse_argtok(&p[i + 1u], col, row);
            
            // if no valid conversion specifier was found
            // print out th
            if (row == _row_size) {
                putc(c0);
                for (; j < i + 1u; ++j) {
                    putc(p[j]);
                }
                return op::cnt; ///< continue
            }
            
            using biggest_native_type = long double;
            std::uint8_t magic_memory[sizeof(biggest_native_type)] {0};
            auto p_magic_memory = reinterpret_cast<void*>(&magic_memory);
            ///auto typesz =
            process_va_list(p_magic_memory, arglist, row, col);
            _out_table[row][col](p_magic_memory);
        } else {
            putc(c0);
        }
        return op::nop;
    }
    
};

}

}

}

}

#endif /// KCPPT_IO_PRINTF_STR_AND_INT_HPP
