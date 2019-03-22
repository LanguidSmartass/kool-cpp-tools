/** @file print.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   16.03.2019
 * 
 * @brief  
 * 
 */

#ifndef KCPPT_PRINT_HPP
#define KCPPT_PRINT_HPP

#include <range.hpp>
#include "printf_light.hpp"
#include "io/common/fmt.hpp"

/// TODO: put enable_if-s into a separate headers, they are too generic

namespace kcppt {

namespace prints {

template <template <typename PutcLambda> class Printf = printf_light>
class printer {
private:
    constexpr static auto _printf = printf_light([](char c) noexcept {std::putchar(c);});
    
private:
    struct idx {
        constexpr static std::size_t lf   = 0u;
        constexpr static std::size_t crlf = 1u;
        constexpr static std::size_t cr   = 2u;
    };
    constexpr static const char* endl[3] = { "\n", "\r\n", "\r" };
    
    static std::size_t _idx;

private:
    /**
     * @brief Determine the appropriate format for printf to properly handle std::size_t and std::uintptr_t at compile
     * time.
     * @return A pointer to a string literal.
     */
    [[nodiscard]]
    constexpr static const char* get_size_t_format () {
        return fmt_by_size::udec_f<sizeof(std::size_t)>();
    }

private:
    /**
     * @brief shortcut constants for types
     */
    template <typename V>
    constexpr static auto is_pointer_or_integral =
        std::is_integral_v<V> || std::is_pointer_v<V>;
    
    template <typename V>
    constexpr static auto is_char = std::is_same_v<V, char>;
    
    template <typename V>
    constexpr static auto is_bool = std::is_same_v<V, bool>;
    
    template <typename V>
    constexpr static auto is_unsigned_char = std::is_same_v<V, unsigned char>;
    
    template <typename V>
    constexpr static auto is_signed =
        std::is_signed_v<V> && !is_char<V> && !is_bool<V>;
    
    template <typename V>
    constexpr static auto is_unsigned =
        std::is_unsigned_v<V> && !is_unsigned_char<V> && !is_bool<V>;
    
    /**
     * @brief enable_if shortcut types
     */
    template <typename V>
    using enable_if_ptr_or_integral_t =
        std::enable_if_t<is_pointer_or_integral<V>, V>;
    
    template <typename V>
    using enable_if_char_t = std::enable_if_t<
        is_char<V> || is_unsigned_char<V>,
        V
    >;
    
    template <typename V>
    using enable_if_bool_t = std::enable_if_t<is_bool<V>, V>;
    
    template <typename V>
    using enable_if_signed_t = std::enable_if_t<is_signed<V>, V>;
    
    template <typename V>
    using enable_if_unsigned_t = std::enable_if_t<is_unsigned<V>, V>;
    
public:
    static auto newline_lf  () noexcept { _idx = idx::lf  ; }
    static auto newline_crlf() noexcept { _idx = idx::crlf; }
    static auto newline_cr  () noexcept { _idx = idx::cr  ; }

public:
    using fmt_by_type = fmt::by_type;
    using fmt_by_size = fmt::by_size;

public:
    static auto printf (const char* fmt, ...) noexcept {
        std::va_list arglist;
        va_start(arglist, fmt);
        _printf.vprintf(fmt, arglist);
        va_end(arglist);
    }
    
    static auto putc (char c) noexcept {
        _printf.putchar(c);
    }
    
    static auto println () noexcept {
        printer::printf(endl[_idx]);
    }

public:
    template <typename V, enable_if_char_t<V> = 0>
    static auto print (V v) noexcept {
        putc(v);
    }
    
    template <typename V, enable_if_signed_t<V> = 0>
    static auto print (V v) noexcept {
        printer::printf(fmt_by_type::sdec_f<V>(), v);
    }

    template <typename V, enable_if_unsigned_t<V> = 0>
    static auto print (V v) noexcept {
        printer::printf(fmt_by_type::udec_f<V>(), v);
    }

    template <typename V, enable_if_bool_t<V> = 0>
    static auto print (V v) noexcept {
        printer::printf(v ? "true" : "false");
    }

    template <typename V>
    static auto print (V* v) noexcept {
        printer::printf(fmt::ptr_HEX_f(), v);
    }
    
    static auto print (char* str) noexcept {
        printer::printf(str);
    }
    
    static auto print (const char* str) noexcept {
        printer::printf(str);
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

private:
    template <
        typename V,
        typename = std::enable_if_t<is_pointer_or_integral<V>>
    >
    using always_integral = std::conditional_t<
        std::is_pointer_v<V>, std::uintptr_t, V
    >;
    
    template <
        typename V,
        typename = std::enable_if_t<is_pointer_or_integral<V>>
    >
    [[nodiscard]]
    constexpr static auto integral_cast (V v) -> always_integral<V> {
        if constexpr (std::is_pointer_v<V>) {
            return reinterpret_cast<std::uintptr_t>(v);
        } else {
            return v;
        }
    }
    
public: /// Output format modifier objects
    template <typename V>
    class [[nodiscard]] hex {
        friend printer;
    private:
        always_integral<V> _v;
    public:
        constexpr explicit hex (V v) : _v(integral_cast(v)) {}
    };
    
    template <typename V>
    class [[nodiscard]] HEX {
        friend printer;
    private:
        always_integral<V> _v;
    public:
        constexpr explicit HEX (V v) : _v(integral_cast(v)) {}
    };
    
    template <typename V>
    class [[nodiscard]] oct {
        friend printer;
    private:
        always_integral<V> _v;
    public:
        constexpr explicit oct (V v) : _v(integral_cast(v)) {}
    };
    
    template <typename V>
    class [[nodiscard]] udec {
        friend printer;
    private:
        always_integral<V> _v;
    public:
        constexpr explicit udec (V v) : _v(integral_cast(v)) {}
    };
    
    template <typename V>
    class [[nodiscard]] sdec {
        friend printer;
    private:
        always_integral<V> _v;
    public:
        constexpr explicit sdec (V v) : _v(integral_cast(v)) {}
    };

public: /// Output format modifier users,
        /// a lot of boilerplate code selects the proper output format
    template <typename V>
    static auto print (const hex<V>& obj) noexcept {
        printer::printf(fmt_by_type::hex_f<decltype(obj._v)>(), obj._v);
    }
    
    template <typename V>
    static auto print (const HEX<V>& obj) noexcept {
        printer::printf(fmt_by_type::HEX_f<decltype(obj._v)>(), obj._v);
    }
    
    template <typename V>
    static auto print (const oct<V>& obj) noexcept {
        printer::printf(fmt_by_type::oct_f<decltype(obj._v)>(), obj._v);
    }
    
    template <typename V>
    static auto print (const udec<V>& obj) noexcept {
        printer::printf(fmt_by_type::udec_f<decltype(obj._v)>(), obj._v);
    }
    
    template <typename V>
    static auto print (const sdec<V>& obj) noexcept {
        printer::printf(fmt_by_type::sdec_f<decltype(obj._v)>(), obj._v);
    }

public:
    enum class justify : bool { left, right };
    
    template <typename V>
    class pad {
        friend printer;
    private:
        V _v;
        justify _j;
        char _p;
        std::size_t _w;
        
    public:
        constexpr pad (
            V v, justify j = justify::left, char p = ' ', std::size_t w = 0
        ) noexcept :
            _v(v), _j(j), _p(p), _w(w)
        {}
    };

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
    
    template <
        typename V,
        typename = std::enable_if_t<is_pointer_or_integral<V>>
    >
    [[nodiscard]]
    constexpr static auto _value_print_length (V v) noexcept {
        return _value_print_length(v, 10u);
    }
    
    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (const hex<V>& v) noexcept {
        return _value_print_length(v._v, 16u);
    }
    
    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (const HEX<V>& v) noexcept {
        return _value_print_length(v._v, 16u);
    }
    
    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (const oct<V>& v) noexcept {
        return _value_print_length(v._v, 8u);
    }
    
    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (const sdec<V>& v) noexcept {
        return _value_print_length(v._v, 10u);
    }
    
    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_length (const udec<V>& v) noexcept {
        return _value_print_length(v._v, 10u);
    }
    
    template <typename V>
    [[nodiscard]]
    constexpr static auto _value_print_sign_and_reverse (V& v) noexcept {
        if (v < 0) {
            v = -v;
            print('-');
        }
    }

public:
    template <
        typename V,
        typename = std::enable_if_t<
            !is_pointer_or_integral<decltype(pad<V>()._v)>
        >
    >
    static auto print (const pad<V>& obj) noexcept {
        auto l = _value_print_length(obj._v);
        if (obj._j == justify::right) {
            print(obj._v);
            _print_padding(l, obj._w, ' ');
        } else {
            auto v = obj._v;
            if constexpr (std::is_signed_v<decltype(v)>) {
                _value_print_sign_and_reverse(v);
            }
            _print_padding(l, obj._w, obj._p);
            print(v);
        }
    }
    
};

template <class C>
std::size_t printer<C>::_idx = printer::idx::lf;

}

}

#endif /// KCPPT_PRINT_HPP
