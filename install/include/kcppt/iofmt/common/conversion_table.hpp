/** @file conversion_specifiers.hpp
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
 * @brief  This table is implemented using the following web resource:
 *         https://en.cppreference.com/w/cpp/io/c/fprintf
 *
 *         The only difference is that specifiers 'n' and 'p' follow
 *         before floating point specifiers because, in my opinion, it will
 *         be easier to divide this table for some implementations like
 *         'integer-only-capable printf'/'float-only-capable printf'
 *         'all-capable printf'. Division can be made simply by restricting
 *         array accesses by the min/max indices.
 */

#ifndef KCPPT_IOFMT_COMMON_CONVERSION_TABLE_HPP
#define KCPPT_IOFMT_COMMON_CONVERSION_TABLE_HPP

#include <array>

namespace kcppt {

namespace iofmt {

namespace common {

namespace conversion_table {

namespace specifiers {

constexpr static auto values = std::array<char, 17u> {
/** char values and C-string pointers */
/**  0 */    'c',
/**  1 */    's',
/** integral values */
/**  2 */    'd', /// 'i', please handle it separately
/**  3 */    'o',
/**  4 */    'x', /// 'x' separate because changes the output to lowercase hex
/**  5 */    'X', /// 'X' separate because changes the output to uppercase hex
/**  6 */    'u',
/** implementation-specific pointer value */
/**  7 */    'p',
/** number of characters written so far (the only output parameter) */
/**  8 */    'n',
/** floating point values */
/**  9 */    'f',
/** 10 */    'F',
/** 11 */    'e',
/** 12 */    'E',
/** 13 */    'a',
/** 14 */    'A',
/** 15 */    'g',
/** 16 */    'G'
};
    
struct idx {
    constexpr static auto c =  0u;
    constexpr static auto s =  1u;
    constexpr static auto d =  2u; constexpr static auto i = d;
    constexpr static auto o =  3u;
    constexpr static auto x =  4u;
    constexpr static auto X =  5u;
    constexpr static auto u =  6u;
    constexpr static auto p =  7u;
    constexpr static auto n =  8u;
    constexpr static auto f =  9u;
    constexpr static auto F = 10u;
    constexpr static auto e = 11u;
    constexpr static auto E = 12u;
    constexpr static auto a = 13u;
    constexpr static auto A = 14u;
    constexpr static auto g = 15u;
    constexpr static auto G = 16u;
};
    
}

namespace length_modifiers {

constexpr static auto values = std::array<const char*, 9u>{
/**  0 */    "hh",
/**  1 */    "h" ,
/**  2 */    ""  ,
/**  3 */    "l" ,
/**  4 */    "ll",
/**  5 */    "j", /// intmax_t/uintmax_t
/**  6 */    "z", /// size_t, signed/unsigned
/**  7 */    "t", /// ptrdiff_t, signed/unsigned
/**  8 */    "L"  /// long double (floats only)
};

struct idx {
    constexpr static auto _hh = 0u;
    constexpr static auto __h = 1u;
    constexpr static auto ___ = 2u;
    constexpr static auto __l = 3u;
    constexpr static auto _ll = 4u;
    constexpr static auto __j = 5u;
    constexpr static auto __z = 6u;
    constexpr static auto __t = 7u;
    constexpr static auto __L = 8u;
};
    
}

}

}

}

}

#endif /// KCPPT_IOFMT_COMMON_CONVERSION_TABLE_HPP
