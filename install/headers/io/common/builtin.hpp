/** @file builtin.hpp
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

#ifndef KCPPT_IO_COMMON_BUILTIN_HPP
#define KCPPT_IO_COMMON_BUILTIN_HPP

#include <cinttypes>
#include <type_traits>
#include <utility>
#include <climits>

namespace kcppt {

namespace io {

namespace common {

namespace builtin {

namespace type {

using _n_a = void;
using __ch = char;
using _wch = wchar_t;
using _win = wint_t;
using _sch = signed char;
using _uch = unsigned char;
using _ssh = short;
using _ush = unsigned short;
using _sin = int;
using _uin = unsigned int;
using _slg = long;
using _ulg = unsigned long;
using _sll = long long;
using _ull = unsigned long long;
using ____ptr = void*;

using __chptr = __ch*;
using _wchptr = _wch*;

}

namespace size {

constexpr static auto _n_a = 0u;
constexpr static auto __ch = sizeof(type::__ch);
constexpr static auto _wch = sizeof(type::_wch);
constexpr static auto _win = sizeof(type::_win);
constexpr static auto _sch = sizeof(type::_sch);
constexpr static auto _uch = sizeof(type::_uch);
constexpr static auto _ssh = sizeof(type::_ssh);
constexpr static auto _ush = sizeof(type::_ush);
constexpr static auto _sin = sizeof(type::_sin);
constexpr static auto _uin = sizeof(type::_uin);
constexpr static auto _slg = sizeof(type::_slg);
constexpr static auto _ulg = sizeof(type::_ulg);
constexpr static auto _sll = sizeof(type::_sll);
constexpr static auto _ull = sizeof(type::_ull);

constexpr static auto ____ptr = sizeof(type::____ptr);
constexpr static auto __chptr = sizeof(type::__chptr);
constexpr static auto _wchptr = sizeof(type::_wchptr);

}

namespace out {

template <typename PutcFunctor, const PutcFunctor& putc>
class ascii {
public:
    static auto character (char c) noexcept {
        putc(c);
    }
    
    static auto string (const char* s) noexcept {
        while (*s != '\0') {
            putc(*s);
            ++s;
        }
    }
};

template <typename PutcFunctor, const PutcFunctor& putc>
class integrals {
private:
    template <
        typename T, std::enable_if_t<std::is_unsigned_v<T>>* = nullptr
    >
    static auto _decimal (T i) noexcept {
        /******************************/
        /// u64, aka unsigned long long takes at most 20 decimal symbols
        char decdigits[20u];
        auto sz = std::size_t(0u);
        auto min = false;
        
        if (i == 0u) { /// if already zero
            decdigits[sz++] = 0x30u;
        } else {
            while (i != 0u) {
                decdigits[sz++] = static_cast<char>((i % 10u) + 0x30u);
                i /= 10u;
            }
        }
        while (sz != 0u) {
            putc(decdigits[--sz]);
        }
    }
    
    template <
        typename T, std::enable_if_t<std::is_signed_v<T>>* = nullptr
    >
    static auto _decimal (T i, bool ignore_sign = true) noexcept {
        /******************************/
        /// s64, aka signed   long long takes at most 19 decimal symbols
        /// plus the '-' sign if negative
        char decdigits[20u];
        auto sz = std::size_t(0u);
        
        if (i == 0u) { /// if already zero
            decdigits[sz++] = 0x30u;
        } else {
            auto min = false;
            auto neg = false;
            
            if (i < 0) {
                neg = true;
                /// comparison between signed and unsigned
//                    long long i_hack_from_warning = i;
                if (i == LLONG_MIN) {
                    min = true;
                    ++i *= (-1);
                } else {
                    i = -i;
                }
            }
            
            while (i != 0u) {
                decdigits[sz++] = static_cast<char>((i % 10u) + 0x30u);
                i /= 10u;
            }
            
            if (neg) {
                if (!ignore_sign) {
                    decdigits[sz++] = '-';
                }
                if (min) {
                    ++decdigits[0u];
                }
            }
            
        }
        
        while (sz != 0u) {
            putc(decdigits[--sz]);
        }
    }
    
    static auto _octal (unsigned long long o) noexcept {
        /// u64, aka unsigned long long takes at most 22 octal symbols
        char octdigits[22u];
        auto sz = std::size_t(0u);
        if (o == 0u) {
            octdigits[0u] = '0';
            sz = 1u;
        }
        while (o != 0u) {
            octdigits[sz++] = static_cast<char>((o & 7u) + 0x30u);
            o >>= 3u;
        }
        while (sz != 0u) {
            putc(octdigits[--sz]);
        }
    }
    
    enum class hex_case_t : bool {
        lower, upper
    };
    
    static auto _hexadecimal (
        unsigned long long x, hex_case_t hcase = hex_case_t::lower
    ) noexcept {
        // u64, aka unsigned long long takes at most 16 hexadecimal symbols
        char hexdigits[16u];
        auto sz = std::size_t(0u);
        if (x == 0u) {
            hexdigits[0u] = '0';
            sz = 1u;
        }
        auto lowercase = (hcase == hex_case_t::lower);
        while (x != 0u) {
            auto num = x & 15u;
            auto offs = (num <= 9u) ? 0x30u : lowercase ? 0x57u : 0x37u;
            hexdigits[sz++] = static_cast<char>(num + offs);
            x >>= 4u;
        }
        while (sz != 0u) {
            putc(hexdigits[--sz]);
        }
    }

public:
    /**
     * @brief Prints the negative integers without the sign.
     *        Positive integers are printed as usual.
     * @param i
     * @return
     */
    static auto decimal_signed_no_negative (signed long long i) noexcept {
        _decimal<decltype(i)>(i, true);
    }
    
    /**
     * @brief Prints all signed integers normally.
     * @param i
     * @return
     */
    static auto decimal_signed_with_negative (signed long long i) noexcept {
        _decimal<decltype(i)>(i, false);
    }
    
    static auto decimal_unsigned (unsigned long long i) noexcept {
        _decimal<decltype(i)>(i);
    }
    
    static auto octal (unsigned long long o) noexcept {
        _octal(o);
    }
    
    static auto hexadecimal_lowercase (unsigned long long x) noexcept {
        _hexadecimal(x, hex_case_t::lower);
    }
    
    static auto hexadecimal_uppercase (unsigned long long X) noexcept {
        _hexadecimal(X, hex_case_t::upper);
    }

};

template <typename PutcFunctor, const PutcFunctor& putc>
class floats {
public:

};

}

namespace inp {

}
    
}
    
}

}
    
}
    
#endif /// KCPPT_IO_COMMON_BUILTIN_HPP
