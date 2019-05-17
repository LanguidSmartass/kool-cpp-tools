/** @file conversion.hpp
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

#ifndef KCPPT_IOFMT_COMMON_CONVERSION_HPP
#define KCPPT_IOFMT_COMMON_CONVERSION_HPP

#include "builtin.hpp"

namespace kcppt {

namespace iofmt {

namespace common {

namespace conversion {

namespace type {
    using _hhc = builtin::type::_n_a;
    using __hc = builtin::type::_n_a;
    using ___c = builtin::type::__ch;
    using __lc = builtin::type::_win;
    using _llc = builtin::type::_n_a;
    using _hhs = builtin::type::_n_a;
    using __hs = builtin::type::_n_a;
    using ___s = builtin::type::__chptr;
    using __ls = builtin::type::_wchptr;
    using _lls = builtin::type::_n_a;
    using _hhd = builtin::type::_sch;
    using __hd = builtin::type::_ssh;
    using ___d = builtin::type::_sin;
    using __ld = builtin::type::_slg;
    using _lld = builtin::type::_sll;
    using _hho = builtin::type::_uch;
    using __ho = builtin::type::_ush;
    using ___o = builtin::type::_uin;
    using __lo = builtin::type::_ulg;
    using _llo = builtin::type::_ull;
    using _hhx = builtin::type::_uch;
    using __hx = builtin::type::_ush;
    using ___x = builtin::type::_uin;
    using __lx = builtin::type::_ulg;
    using _llx = builtin::type::_ull;
    using _hhX = builtin::type::_uch;
    using __hX = builtin::type::_ush;
    using ___X = builtin::type::_uin;
    using __lX = builtin::type::_ulg;
    using _llX = builtin::type::_ull;
    using _hhu = builtin::type::_uch;
    using __hu = builtin::type::_ush;
    using ___u = builtin::type::_uin;
    using __lu = builtin::type::_ulg;
    using _llu = builtin::type::_ull;
};

namespace size {
    constexpr static auto _hhc = builtin::size::_n_a;
    constexpr static auto __hc = builtin::size::_n_a;
    constexpr static auto ___c = builtin::size::__ch;
    constexpr static auto __lc = builtin::size::_win;
    constexpr static auto _llc = builtin::size::_n_a;
    constexpr static auto _hhs = builtin::size::_n_a;
    constexpr static auto __hs = builtin::size::_n_a;
    constexpr static auto ___s = builtin::size::__chptr;
    constexpr static auto __ls = builtin::size::_wchptr;
    constexpr static auto _lls = builtin::size::_n_a;
    constexpr static auto _hhd = builtin::size::_sch;
    constexpr static auto __hd = builtin::size::_ssh;
    constexpr static auto ___d = builtin::size::_sin;
    constexpr static auto __ld = builtin::size::_slg;
    constexpr static auto _lld = builtin::size::_sll;
    constexpr static auto _hho = builtin::size::_uch;
    constexpr static auto __ho = builtin::size::_ush;
    constexpr static auto ___o = builtin::size::_uin;
    constexpr static auto __lo = builtin::size::_ulg;
    constexpr static auto _llo = builtin::size::_ull;
    constexpr static auto _hhx = builtin::size::_uch;
    constexpr static auto __hx = builtin::size::_ush;
    constexpr static auto ___x = builtin::size::_uin;
    constexpr static auto __lx = builtin::size::_ulg;
    constexpr static auto _llx = builtin::size::_ull;
    constexpr static auto _hhX = builtin::size::_uch;
    constexpr static auto __hX = builtin::size::_ush;
    constexpr static auto ___X = builtin::size::_uin;
    constexpr static auto __lX = builtin::size::_ulg;
    constexpr static auto _llX = builtin::size::_ull;
    constexpr static auto _hhu = builtin::size::_uch;
    constexpr static auto __hu = builtin::size::_ush;
    constexpr static auto ___u = builtin::size::_uin;
    constexpr static auto __lu = builtin::size::_ulg;
    constexpr static auto _llu = builtin::size::_ull;
};

namespace out {

template <typename PutcFunctor, const PutcFunctor& putc>
class ascii {
private:
    using out_t = builtin::out::ascii<PutcFunctor, putc>;

public:
    static auto _hhc (const void* pmem) noexcept {
        (void)pmem;
    }
    static auto __hc (const void* pmem) noexcept {
        (void)pmem;
    }
    static auto ___c (const void* pmem) noexcept {
        using type = conversion::type::___c;
        auto c = *reinterpret_cast<const type*>(pmem);
        out_t::character(c);
    }
    static auto __lc (const void* pmem) noexcept {
        (void)pmem;
    }
    static auto _llc (const void* pmem) noexcept {
        (void)pmem;
    }
    static auto _hhs (const void* pmem) noexcept {
        (void)pmem;
    }
    static auto __hs (const void* pmem) noexcept {
        (void)pmem;
    }
    static auto ___s (const void* pmem) noexcept {
        using type = const conversion::type::___s;
        auto s = *reinterpret_cast<const type*>(pmem);
        out_t::string(s);
    }
    static auto __ls (const void* pmem) noexcept {
        (void)pmem;
    }
    static auto _lls (const void* pmem) noexcept {
        (void)pmem;
    }
};

/// output functions for each integral type and specifier
template <typename PutcFunctor, const PutcFunctor& putc>
class integrals {
private:
    using out_t = builtin::out::integrals<PutcFunctor, putc>;
    
    template <typename T, auto fout>
    static auto _fout (const void* pmem) noexcept {
        T tmp = *reinterpret_cast<const T*>(pmem);
        fout(tmp);
    }
    
public:
    /// default, with negative sign
    static auto _hhd (const void* pmem) noexcept {
        _fout<type::_hhd, out_t::decimal_signed_with_negative>(pmem);
    }
    static auto __hd (const void* pmem) noexcept {
        _fout<type::__hd, out_t::decimal_signed_with_negative>(pmem);
    }
    static auto ___d (const void* pmem) noexcept {
        _fout<type::___d, out_t::decimal_signed_with_negative>(pmem);
    }
    static auto __ld (const void* pmem) noexcept {
        _fout<type::__ld, out_t::decimal_signed_with_negative>(pmem);
    }
    static auto _lld (const void* pmem) noexcept {
        _fout<type::_lld, out_t::decimal_signed_with_negative>(pmem);
    }
    
    /// no negative sign
    static auto _hhd_nn (const void* pmem) noexcept {
        _fout<type::_hhd, out_t::decimal_signed_no_negative>(pmem);
    }
    static auto __hd_nn (const void* pmem) noexcept {
        _fout<type::__hd, out_t::decimal_signed_no_negative>(pmem);
    }
    static auto ___d_nn (const void* pmem) noexcept {
        _fout<type::___d, out_t::decimal_signed_no_negative>(pmem);
    }
    static auto __ld_nn (const void* pmem) noexcept {
        _fout<type::__ld, out_t::decimal_signed_no_negative>(pmem);
    }
    static auto _lld_nn (const void* pmem) noexcept {
        _fout<type::_lld, out_t::decimal_signed_no_negative>(pmem);
    }
    
    static auto _hho (const void* pmem) noexcept {
        using type = conversion::type::_hho;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::octal(tmp);
    }
    static auto __ho (const void* pmem) noexcept {
        using type = conversion::type::__ho;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::octal(tmp);
    }
    static auto ___o (const void* pmem) noexcept {
        using type = conversion::type::___o;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::octal(tmp);
        
    }
    static auto __lo (const void* pmem) noexcept {
        using type = conversion::type::__lo;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::octal(tmp);
    }
    static auto _llo (const void* pmem) noexcept {
        using type = conversion::type::_llo;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::octal(tmp);
    }
    static auto _hhx (const void* pmem) noexcept {
        using type = conversion::type::_hhx;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::hexadecimal_lowercase(tmp);
    }
    static auto __hx (const void* pmem) noexcept {
        using type = conversion::type::__hx;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::hexadecimal_lowercase(tmp);
    }
    static auto ___x (const void* pmem) noexcept {
        using type = conversion::type::___x;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::hexadecimal_lowercase(tmp);
    }
    static auto __lx (const void* pmem) noexcept {
        using type = conversion::type::__lx;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::hexadecimal_lowercase(tmp);
    }
    static auto _llx (const void* pmem) noexcept {
        using type = conversion::type::_llx;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::hexadecimal_lowercase(tmp);
    }
    static auto _hhX (const void* pmem) noexcept {
        using type = conversion::type::_hhX;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::hexadecimal_uppercase(tmp);
    }
    static auto __hX (const void* pmem) noexcept {
        using type = conversion::type::__hX;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::hexadecimal_uppercase(tmp);
    }
    static auto ___X (const void* pmem) noexcept {
        using type = conversion::type::___X;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::hexadecimal_uppercase(tmp);
    }
    static auto __lX (const void* pmem) noexcept {
        using type = conversion::type::__lX;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::hexadecimal_uppercase(tmp);
    }
    static auto _llX (const void* pmem) noexcept {
        using type = conversion::type::_llX;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::hexadecimal_uppercase(tmp);
    }
    static auto _hhu (const void* pmem) noexcept {
        using type = conversion::type::_hhu;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::decimal_unsigned(tmp);
    }
    static auto __hu (const void* pmem) noexcept {
        using type = conversion::type::__hu;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::decimal_unsigned(tmp);
    }
    static auto ___u (const void* pmem) noexcept {
        using type = conversion::type::___u;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::decimal_unsigned(tmp);
    }
    static auto __lu (const void* pmem) noexcept {
        using type = conversion::type::__lu;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::decimal_unsigned(tmp);
    }
    static auto _llu (const void* pmem) noexcept {
        using type = conversion::type::_llu;
        type tmp = *reinterpret_cast<const type*>(pmem);
        out_t::decimal_unsigned(tmp);
    }
};

template <typename PutcFunctor, const PutcFunctor& putc>
class floats {
private:
    using out_t = builtin::out::floats<PutcFunctor, putc>;

};

}

namespace inp {

}

}

}

}

}

#endif /// KCPPT_IOFMT_COMMON_CONVERSION_HPP
