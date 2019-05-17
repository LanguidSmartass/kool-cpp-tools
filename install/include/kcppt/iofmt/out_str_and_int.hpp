/** @file out_str_and_int.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   16.03.2019
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

#ifndef KCPPT_IOFMT_OUT_STR_AND_INT_HPP
#define KCPPT_IOFMT_OUT_STR_AND_INT_HPP

#include "../kcppt/range.hpp"
#include "../kcppt/util.hpp"
#include "common/fmt.hpp"
#include "printf/str_and_int.hpp"

/// TODO: put enable_if-s into a separate headers, they are too generic

namespace kcppt {

namespace iofmt {

namespace out {

namespace fmt {

template <
    typename V,
    util::enable_if_integral_or_pointer_t<V>* = nullptr
>
using always_integral = std::conditional_t<
    std::is_pointer_v<V>,
    std::conditional_t<
        std::is_signed_v<V>,
        std::intptr_t,
        std::uintptr_t
    >,
    V
>;

template <
    typename V,
    util::enable_if_integral_or_pointer_t<V>* = nullptr
>
[[nodiscard]]
constexpr static auto integral_cast (V v) -> always_integral<V> {
    if constexpr (std::is_pointer_v<V>) {
        return reinterpret_cast<
            std::conditional_t<
                std::is_signed_v<V>,
                std::intptr_t,
                std::uintptr_t
            >
            >(v);
    } else {
        return v;
    }
}

template <typename V>
struct [[nodiscard]] hex {
    always_integral<V> _v;
    constexpr explicit hex (V v) noexcept : _v(integral_cast(v)) {}
};

template <typename V>
struct [[nodiscard]] HEX {
    always_integral<V> _v;
    constexpr explicit HEX (V v) noexcept : _v(integral_cast(v)) {}
};

template <typename V>
struct [[nodiscard]] oct {
    always_integral<V> _v;
    constexpr explicit oct (V v) noexcept : _v(integral_cast(v)) {}
};

template <typename V>
struct [[nodiscard]] udec {
    always_integral<V> _v;
    constexpr explicit udec (V v) noexcept : _v(integral_cast(v)) {}
};

template <typename V>
struct [[nodiscard]] sdec {
    always_integral<V> _v;
    constexpr explicit sdec (V v) noexcept : _v(integral_cast(v)) {}
};

enum class jst : bool { left, right };

template <typename V>
struct pad {
    V _v;
    jst _j;
    char _p;
    std::size_t _w;

    constexpr pad (
        V v, jst j = jst::left, char p = ' ', std::size_t w = 0u
    ) noexcept :
        _v(v), _j(j), _p(p), _w(w)
    {}
};

}

template <class Printf>
class str_and_int {
public:
    using fmtints_by_type = common::fmt::out::integrals::by_type;
    using fmtints_by_size = common::fmt::out::integrals::by_size;
    using fmtptr = common::fmt::out::integrals::ptr;

public:
    static auto newline_lf  () noexcept { _idx = idx::lf  ; }
    static auto newline_crlf() noexcept { _idx = idx::crlf; }
    static auto newline_cr  () noexcept { _idx = idx::cr  ; }

public:
    static auto putchar (char c) noexcept {
        _printf.putchar(c);
    }
    
    static auto println () noexcept {
        _printf.printf(_endl[_idx]);
    }
    
    template <typename V, util::enable_if_char_t<V>* = nullptr>
    static auto print (V v) noexcept {
        _printf.putchar(v);
    }

    template <typename V, util::enable_if_signed_t<V>* = nullptr>
    static auto print (V v) noexcept {
        _printf.printf(fmtints_by_type::sdec_v<V>, v);
    }

    template <typename V, util::enable_if_unsigned_t<V>* = nullptr>
    static auto print (V v) noexcept {
        _printf.printf(fmtints_by_type::udec_v<V>, v);
    }

    template <typename V, util::enable_if_bool_t<V>* = nullptr>
    static auto print (V v) noexcept {
        _printf.printf(v ? "true" : "false");
    }

    template <typename V>
    static auto print (V* v) noexcept {
        _printf.printf(fmtptr::HEX_v, v);
    }

    static auto print (char* str) noexcept {
        _printf.printf(str);
    }

    static auto print (const char* str) noexcept {
        _printf.printf(str);
    }

    template <typename PT0, typename PT1, typename ... PTs>
    static auto print (PT0&& pt0, PT1&& pt1, PTs&&...pts) noexcept {
        print(std::forward<PT0>(pt0));
        print(std::forward<PT1>(pt1));
        (print(std::forward<PTs>(pts)), ...);
    }

    template <typename PT, typename ... PTs>
    static auto println (PT&& pt, PTs&&...pts) noexcept {
        print(std::forward<PT>(pt), std::forward<PTs>(pts)...);
        println();
    }

public:
    template <typename V>
    static auto print (const fmt::hex<V>& obj) noexcept {
        auto mul = _print_negative_sign_if_any(obj);
        _printf.printf(fmtints_by_type::hex_v<decltype(obj._v)>, mul * obj._v);
    }

    template <typename V>
    static auto print (const fmt::HEX<V>& obj) noexcept {
        auto mul = _print_negative_sign_if_any(obj);
        _printf.printf(fmtints_by_type::HEX_v<decltype(obj._v)>, mul * obj._v);
    }

    template <typename V>
    static auto print (const fmt::oct<V>& obj) noexcept {
        auto mul = _print_negative_sign_if_any(obj);
        _printf.printf(fmtints_by_type::oct_v<decltype(obj._v)>, mul * obj._v);
    }

    template <typename V>
    static auto print (const fmt::udec<V>& obj) noexcept {
        auto mul = _print_negative_sign_if_any(obj);
        _printf.printf(fmtints_by_type::udec_v<decltype(obj._v)>, mul * obj._v);
    }

    template <typename V>
    static auto print (const fmt::sdec<V>& obj) noexcept {
        auto mul = _print_negative_sign_if_any(obj);
        _printf.printf(fmtints_by_type::sdec_v<decltype(obj._v)>, mul * obj._v);
    }

public:
    template <typename V>
    static auto print (const fmt::pad<V>& pad) noexcept {
        auto l = _value_print_length(pad._v);
        if (pad._j == fmt::jst::right) {
            print(pad._v);
            _print_padding(l, pad._w, ' ');
        } else {
            auto mul = _print_negative_sign_if_any(pad._v);
            _print_padding(l, pad._w, pad._p);
            _print_with_mul(mul, pad._v);
        }
    }

private:
    constexpr static auto _printf = Printf();
    constexpr static auto fmt_size_t = fmtints_by_type::udec_v<std::size_t>;
    
    struct idx {
        constexpr static auto lf   = 0u;
        constexpr static auto crlf = 1u;
        constexpr static auto cr   = 2u;
    };
    constexpr static const char* _endl[3u] = { "\n", "\r\n", "\r" };
    static std::size_t _idx;

private:
    template <
        typename V,
        util::enable_if_signed_or_pointer_t<V>* = nullptr
    >
    using always_signed = std::conditional_t<
        std::is_pointer_v<V>, std::intptr_t, V
    >;
    
    template <
        typename V
    >
    using always_unsigned = std::conditional_t<
        std::is_pointer_v<V>, std::uintptr_t, V
    >;
    
    template <
        typename V,
        util::enable_if_signed_or_pointer_t<V>* = nullptr
    >
    [[nodiscard]]
    constexpr static auto signed_cast (V v) -> always_signed<V> {
        if constexpr (std::is_pointer_v<V>) {
            return reinterpret_cast<std::intptr_t>(v);
        } else {
            return v;
        }
    }
    
    template <
        typename V,
        util::enable_if_unsigned_or_pointer_t<V>* = nullptr
    >
    [[nodiscard]]
    constexpr static auto unsigned_cast (V v) -> always_unsigned<V> {
        if constexpr (std::is_pointer_v<V>) {
            return reinterpret_cast<std::uintptr_t>(v);
        } else {
            return v;
        }
    }

private:
    static auto _print_padding (std::size_t l, std::size_t w, char p) noexcept {
        if (w > l) {
            for (auto i : range::range(w - l)) {
                print(p);
            }
        }
    }

    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (
        V v, std::size_t div
    ) noexcept -> std::size_t {
        if (v == 0) {
            return 1u;
        }
        auto cnt = std::size_t{0u};
        if constexpr (std::is_signed_v<V>) {
            if (v < 0) {
                v *= -1;
            }
        }
        while (v) {
            v /= div;
            ++cnt;
        }
        return cnt;
    }

    template <typename V, util::enable_if_integral_or_pointer_t<V>* = nullptr>
    [[nodiscard]]
    constexpr static auto _value_print_length (V v) noexcept {
        return _value_print_length(v, 10u);
    }

    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (const fmt::hex<V>& v) noexcept {
        return _value_print_length(v._v, 16u);
    }

    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (const fmt::HEX<V>& v) noexcept {
        return _value_print_length(v._v, 16u);
    }

    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (const fmt::oct<V>& v) noexcept {
        return _value_print_length(v._v, 8u);
    }

    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (const fmt::sdec<V>& v) noexcept {
        return _value_print_length(v._v, 10u);
    }

    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (const fmt::udec<V>& v) noexcept {
        return _value_print_length(v._v, 10u);
    }

    template <typename V, util::enable_if_class_t<V>* = nullptr>
    static auto _print_negative_sign_if_any (const V& v) noexcept -> int {
        if constexpr (!traits::is_signed_v<decltype(v._v)>) {
            return 1;
        }
        if (v._v >= 0) {
            return 1;
        }
        _printf.putchar('-');
        return -1;
    }
    
    template <typename V, util::enable_if_integral_or_pointer_t<V>* = nullptr>
    static auto _print_negative_sign_if_any (V v) noexcept -> int {
        if constexpr (!traits::is_signed_v<V>) {
            return 1;
        }
        if (v >= 0) {
            return 1;
        }
        _printf.putchar('-');
        return -1;
    }
    
    template <typename V, util::enable_if_class_t<V>* = nullptr>
    static auto _print_with_mul (int mul, const V& v) noexcept {
        print(mul * v._v);
    }
    
    template <typename V, util::enable_if_integral_or_pointer_t<V>* = nullptr>
    static auto _print_with_mul (int mul, V v) noexcept {
        print(mul * v);
    }
    
};

template <class C>
std::size_t str_and_int<C>::_idx = str_and_int::idx::lf;

}

}

}

#endif /// KCPPT_IOFMT_OUT_STR_AND_INT_HPP
