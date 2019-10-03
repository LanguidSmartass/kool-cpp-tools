/** @file c_string.hpp
 *
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   24.03.2019
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
 
#ifndef KCPPT_C_STRING_HPP
#define KCPPT_C_STRING_HPP

#include "range.hpp"

namespace kcppt::c_string {

/**
 * @brief
 *
 *
 */

constexpr auto strcmp (const char *lhs, const char *rhs) noexcept -> int {
    while (true) {
        auto lc = int {*lhs};
        auto rc = int {*rhs};
    
        auto diff = lc - rc;
        
        if (!lc || !rc) {
            return diff;
        } else if (!diff) {
            ++lhs;
            ++rhs;
            continue;
        }
        
        return diff;
    }
}

constexpr auto strlen (const char* src) noexcept -> std::size_t {
//    return *src ? strlen(++src) + 1u : 0u;
    auto len = std::size_t {};
    while (*src) {
        ++len;
        ++src;
    }
    return len;
}

constexpr auto strnlen (const char *src , std::size_t maxcnt)
noexcept -> std::size_t {
    auto len = std::size_t {};
    while (*src || (len < maxcnt)) {
        ++len;
        ++src;
    }
    return len;
}

/**
 * @brief
 *
 *
 */

/**
 * @brief
 */
using is_condition_f = auto (*)(char) -> bool;

[[nodiscard]]
constexpr auto is_ascii (char c) noexcept {
    return (c >= 0) && (c <= 0x7F);
}

[[nodiscard]]
constexpr auto is_lf (char c) noexcept {
    return c == '\n';
}

[[nodiscard]]
constexpr auto is_cr (char c) noexcept {
    return c == '\r';
}

[[nodiscard]]
constexpr auto is_tab (char c) noexcept {
    return c == '\t';
}

[[nodiscard]]
constexpr auto is_space (char c) noexcept {
    return c == ' ';
}

[[nodiscard]]
constexpr auto is_upper (char c) noexcept {
    return ((c >= 0x41u) && (c <= 0x5Au));
}

[[nodiscard]]
constexpr auto is_lower (char c) noexcept {
    return (c >= 0x61u) && (c <= 0x7Au);
}

[[nodiscard]]
constexpr auto is_printing (char c) noexcept {
    return c >= 0x20u;
}

[[nodiscard]]
constexpr auto is_nonprint (char c) noexcept {
    return c <= 0x1F;
}
/// covered
[[nodiscard]]
constexpr auto is_bin (char c) noexcept {
    return (c == 0x30u) || (c == 0x31u);
}

[[nodiscard]]
constexpr auto is_oct (char c) noexcept {
    return (c >= 0x30u) && (c <= 0x37u);
}

[[nodiscard]]
constexpr auto is_dec (char c) noexcept {
    return (c >= 0x30u) && (c <= 0x39u);
}

[[nodiscard]]
constexpr auto is_hex_low (char c) noexcept {
    return is_dec(c) || ((c >= 0x61u) && (c <= 0x66u));
}

[[nodiscard]]
constexpr auto is_hex_up (char c) noexcept {
    return is_dec(c) || ((c >= 0x41u) && (c <= 0x46u));
}

[[nodiscard]]
constexpr auto is_hex (char c) noexcept {
    return is_hex_low(c) || is_hex_up(c);
}

/**
 * @brief Heuristics function, checks if data is an ASCII string.
 *  The default call: is_c_string(str, N)
 *  returns true if:
 *  the last character (str[size - 1]) is a null terminator AND
 *  all other characters are 'visible characters', meaning 'is_visible_char(c)' returned true on every char from
 *  str[0] to str[size - 2].
 *
 * However, the condition whether the string is 'ASCII' can be expanded by providing additional conditional functions
 * as function template parameters. For example, one may want to sort out strings that contain non-print ASCII chars:
 *     bell (\a, 0x07), backspace (\b, 0x08), tab (\t, 0x09), linefeed (\n, 0x0A),
 *     vertical tab (\v, 0x0B), new page (\f, 0x0C), carriage return (\r, 0x0D)
 *  to be a C-string as well,
 *
 *  Modified call: is_c_string<is_escape_char>(str, N)
 *
 *  Or, if you have a sequence of null-terminated strings (like "str1\0str2\0str3\0str4") you can call
 *
 *  is_c_string<is_null_terminator>(str, N)
 *
 *  And the result will be true.
 *
 *  Or you can do both for strings like this "\tstr1\n\0str2\0\rstr3\0str4\f":
 *
 *  is_c_string<is_null_terminator, is_escape_char>(str, N)
 *
 * You can provide your own custom pattern matchers.
 *
 * @param src -- pointer to the first byte in the byte sequence
 * @param size -- size of the byte sequence to be parsed
 * @return true if the default condition (is_visible_char) and additional conditions from the template argument list
 *         return true for every byte, except for the very last byte (which is expected to be a null-terminator);
 *         false if otherwise
 */
template <is_condition_f F0 = is_printing, is_condition_f ... Fs>
[[nodiscard]]
constexpr auto is_c_string (const char* str) noexcept {
    if (!str)
        return false;
    
    /// a simple local lambda tester,
    /// always runs at least one check -- 'is_visible_char(c)'
    constexpr auto bool_or_all_conditions = [](char c) -> bool {
        return F0(c) || (Fs(c) || ...);
    };
    
    auto result = true;
    
    while (true) {
        auto c = *str;
        if (!c) {
            return result;
        } else if (bool_or_all_conditions(c)) {
            ++str;
            continue;
        }
        result = false;
        break;
    }
    
    return result;
}

}

#endif /// KCPPT_C_STRING_HPP
