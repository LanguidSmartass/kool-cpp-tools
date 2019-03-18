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
#include "fmt.hpp"

namespace kcppt {

namespace prints {

template <class Printf = printf_light<>>
class printer {
private:
    constexpr static auto _printf = Printf();
    
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
    constexpr static const char* get_size_t_format () {
#if __cplusplus >= 201402L
        constexpr auto sz = sizeof(std::size_t);
        constexpr auto ret = sz == 8u ? "%" PRIu64 : sz == 4u ? "%" PRIu32 : sz == 2u ? "%" PRIu16 : sz == 1u ? "%" PRIu8 : "";
        static_assert(ret[0] != '\0', "Error detecting sizeof(std::size_t)");
        return ret;
#else
        return fmt_by_size::udec_f<sizeof(std::size_t)>();
#endif
    }

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
    
    static auto println () noexcept {
        printer::printf(endl[_idx]);
    }

public:
    template <typename V>
    static auto print (V v) noexcept {
        if constexpr (std::is_same_v<V, char>) {
            printer::printf("%c", v);
        } else if constexpr (std::is_signed_v<V>) {
            printer::printf(fmt_by_type::sdec_f<V>(), v);
        } else {
            printer::printf(fmt_by_type::udec_f<V>(), v);
        }
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
    
    static auto print (bool b) noexcept {
        printer::printf(b ? "true" : "false");
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
    template <typename V>
    using always_integral = std::conditional_t<
        std::is_pointer_v<V>, std::uintptr_t, V
    >;
    
    template <typename V>
    constexpr static auto integral_cast (V v) {
        if constexpr (std::is_pointer_v<V>) {
            return reinterpret_cast<std::uintptr_t>(v);
        } else {
            return v;
        }
    }
    
public: /// Output format modifier objects
    template <typename V>
    class hex {
        friend printer;
    private:
        always_integral<V> _v;
    public:
        explicit hex (V v) : _v(integral_cast(v)) {}
    };
    
    template <typename V>
    class HEX {
        friend printer;
    private:
        always_integral<V> _v;
    public:
        explicit HEX (V v) : _v(integral_cast(v)) {}
    };
    
    template <typename V>
    class oct {
        friend printer;
    private:
        always_integral<V> _v;
    public:
        explicit oct (V v) : _v(integral_cast(v)) {}
    };
    
    template <typename V>
    class udec {
        friend printer;
    private:
        always_integral<V> _v;
    public:
        explicit udec (V v) : _v(integral_cast(v)) {}
    };
    
    template <typename V>
    class sdec {
        friend printer;
    private:
        always_integral<V> _v;
    public:
        explicit sdec (V v) : _v(integral_cast(v)) {}
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
        pad (V v, justify j = justify::left, char p = ' ', std::size_t w = 0)
        noexcept :
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
    
    template <std::size_t Div, typename V>
    static auto _value_print_length (V v) noexcept -> std::size_t {
        if (v == 0) {
            return 1u;
        }
        auto cnt = std::size_t{0u};
        if constexpr (std::is_signed_v<V>) {
            if (v < 0) {
                v *= -1;
                ++cnt;
            }
        }
        while (v) {
            v /= Div;
            ++cnt;
        }
        return cnt;
    }
    
    template <typename V>
    static auto _value_print_length (const hex<V>& v) noexcept {
        return _value_print_length<16u>(v._v);
    }
    
    template <typename V>
    static auto _value_print_length (const HEX<V>& v) noexcept {
        return _value_print_length<16u>(v._v);
    }
    
    template <typename V>
    static auto _value_print_length (const oct<V>& v) noexcept {
        return _value_print_length<8u>(v._v);
    }
    
    template <typename V>
    static auto _value_print_length (const sdec<V>& v) noexcept {
        return _value_print_length<10u>(v._v);
    }
    
    template <typename V>
    static auto _value_print_length (const udec<V>& v) noexcept {
        return _value_print_length<10u>(v._v);
    }

public:
    template <typename V>
    static auto print (const pad<V>& obj) noexcept {
        auto l = _value_print_length(obj._v);
        if (obj._j == justify::right) {
            print(obj._v);
            _print_padding(l, obj._w, ' ');
        } else {
            if constexpr (std::is_signed_v<V>) {
                auto v = std::make_unsigned_t<decltype(obj._v)> {obj._v._v};
                if (obj._v < 0) {
                    v = -obj._v;
                    print('-');
                }
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
