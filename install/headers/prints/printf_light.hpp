/** @file printf_light.hpp
 *
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   15.03.2019
 *
 * @brief  light version of printf
 */

#ifndef KCPPT_PRINTS_PRINTF_LIGHT_HPP
#define KCPPT_PRINTS_PRINTF_LIGHT_HPP

#include <cstdarg>
#include <cinttypes>
#include <climits>
#include <cwchar>
#include <type_traits>
#include <cstdio>

namespace kcppt {

namespace prints {

constexpr static auto std_putchar_lambda =
    [](char c) noexcept {std::putchar(c);};

template <
    class LLOUT = decltype(std_putchar_lambda),
    LLOUT& lambda = std_putchar_lambda,
    std::size_t maxfmtlen = 256u
>
class printf_light {
private:
    constexpr static auto _putchar_lambda = lambda;
    
private:
    constexpr static char _conv_specs[] = {
        'c',
        's',
        'd', /// 'i', handled in 'parse_conv_spec'
        'o',
        'x', /// 'x' separate because changes the output to lowercase hex
        'X', /// 'X' separate because changes the output to uppercase hex
        'u',
    };

    constexpr static const char* _length_mods[] = {
        "hh",
        "h" ,
        ""  ,
        "l" ,
        "ll",
    };

    constexpr static const std::size_t _conv_specs_cnt  = sizeof(_conv_specs)  / sizeof(char);
    constexpr static const std::size_t _length_mods_cnt = sizeof(_length_mods) / sizeof(char*);

    struct types {
        struct _t {
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
        };
        struct sz {
            constexpr static const auto _n_a = 0u;
            constexpr static const auto __ch = sizeof(_t::__ch);
            constexpr static const auto _wch = sizeof(_t::_wch);
            constexpr static const auto _win = sizeof(_t::_win);
            constexpr static const auto _sch = sizeof(_t::_sch);
            constexpr static const auto _uch = sizeof(_t::_uch);
            constexpr static const auto _ssh = sizeof(_t::_ssh);
            constexpr static const auto _ush = sizeof(_t::_ush);
            constexpr static const auto _sin = sizeof(_t::_sin);
            constexpr static const auto _uin = sizeof(_t::_uin);
            constexpr static const auto _slg = sizeof(_t::_slg);
            constexpr static const auto _ulg = sizeof(_t::_ulg);
            constexpr static const auto _sll = sizeof(_t::_sll);
            constexpr static const auto _ull = sizeof(_t::_ull);

            constexpr static const auto ____ptr = sizeof(_t::____ptr);
            constexpr static const auto __chptr = sizeof(_t::__chptr);
            constexpr static const auto _wchptr = sizeof(_t::_wchptr);
        };
    };

    struct cspec {
        struct _t {
            using _hhc = typename types::_t::_n_a;
            using __hc = typename types::_t::_n_a;
            using ___c = typename types::_t::__ch;
            using __lc = typename types::_t::_win;
            using _llc = typename types::_t::_n_a;
            using _hhs = typename types::_t::_n_a;
            using __hs = typename types::_t::_n_a;
            using ___s = typename types::_t::__chptr;
            using __ls = typename types::_t::_wchptr;
            using _lls = typename types::_t::_n_a;
            using _hhd = typename types::_t::_sch;
            using __hd = typename types::_t::_ssh;
            using ___d = typename types::_t::_sin;
            using __ld = typename types::_t::_slg;
            using _lld = typename types::_t::_sll;
            using _hho = typename types::_t::_uch;
            using __ho = typename types::_t::_ush;
            using ___o = typename types::_t::_uin;
            using __lo = typename types::_t::_ulg;
            using _llo = typename types::_t::_ull;
            using _hhx = typename types::_t::_uch;
            using __hx = typename types::_t::_ush;
            using ___x = typename types::_t::_uin;
            using __lx = typename types::_t::_ulg;
            using _llx = typename types::_t::_ull;
            using _hhX = typename types::_t::_uch;
            using __hX = typename types::_t::_ush;
            using ___X = typename types::_t::_uin;
            using __lX = typename types::_t::_ulg;
            using _llX = typename types::_t::_ull;
            using _hhu = typename types::_t::_uch;
            using __hu = typename types::_t::_ush;
            using ___u = typename types::_t::_uin;
            using __lu = typename types::_t::_ulg;
            using _llu = typename types::_t::_ull;
        };
        struct sz {
            constexpr static const auto _hhc = types::sz::_n_a;
            constexpr static const auto __hc = types::sz::_n_a;
            constexpr static const auto ___c = types::sz::__ch;
            constexpr static const auto __lc = types::sz::_win;
            constexpr static const auto _llc = types::sz::_n_a;
            constexpr static const auto _hhs = types::sz::_n_a;
            constexpr static const auto __hs = types::sz::_n_a;
            constexpr static const auto ___s = types::sz::____ptr;
            constexpr static const auto __ls = types::sz::____ptr;
            constexpr static const auto _lls = types::sz::_n_a;
            constexpr static const auto _hhd = types::sz::_sch;
            constexpr static const auto __hd = types::sz::_ssh;
            constexpr static const auto ___d = types::sz::_sin;
            constexpr static const auto __ld = types::sz::_slg;
            constexpr static const auto _lld = types::sz::_sll;
            constexpr static const auto _hho = types::sz::_uch;
            constexpr static const auto __ho = types::sz::_ush;
            constexpr static const auto ___o = types::sz::_uin;
            constexpr static const auto __lo = types::sz::_ulg;
            constexpr static const auto _llo = types::sz::_ull;
            constexpr static const auto _hhx = types::sz::_uch;
            constexpr static const auto __hx = types::sz::_ush;
            constexpr static const auto ___x = types::sz::_uin;
            constexpr static const auto __lx = types::sz::_ulg;
            constexpr static const auto _llx = types::sz::_ull;
            constexpr static const auto _hhX = types::sz::_uch;
            constexpr static const auto __hX = types::sz::_ush;
            constexpr static const auto ___X = types::sz::_uin;
            constexpr static const auto __lX = types::sz::_ulg;
            constexpr static const auto _llX = types::sz::_ull;
            constexpr static const auto _hhu = types::sz::_uch;
            constexpr static const auto __hu = types::sz::_ush;
            constexpr static const auto ___u = types::sz::_uin;
            constexpr static const auto __lu = types::sz::_ulg;
            constexpr static const auto _llu = types::sz::_ull;
        };
    };

    // write-out function pointer type
    using fpwrout_t = void(*)(void*);
    // list of 'write-out' functions for each type
    struct wroutimpl {
    private:
        template <typename T>
        static void int_print (T i) {
            /*** compile time ensurance ***/
            static_assert(std::is_integral<T>::value, "Only integral types are allowed to be used by this function");
            /******************************/
            // u64, aka unsigned long long takes at most 20 decimal symbols
            // s64, aka signed   long long takes at most 19 decimal symbols and the '-' sign if negative
            char decdigits[20u];
            std::uint8_t sz = 0u;
            bool neg = false;
            bool min = false;

            if (i == 0) { // if already zero
            	decdigits[sz++] = 0x30;
            } else {
                if constexpr (std::is_signed<T>::value) {
                    if (i < 0) {
                        neg = true;
                        long long i_hack_from_warning = i; /// comparison between signed and unsigned
                        if (i_hack_from_warning == LLONG_MIN) {
                            min = true;
                            ++i *= (-1);
                        } else {
                            i *= (-1);
                        }
                    }
                }
                while (i != 0) {
                    decdigits[sz++] = static_cast<char>((i % 10) + 0x30);
                    i /= 10;
                }
                if (std::is_signed<T>::value) {
                    if (neg) {
                        decdigits[sz++] = '-';
                        if (min) {
                            ++decdigits[0];
                        }
                    }
                }
            }
            while (sz != 0u) {
                _putchar_lambda(decdigits[--sz]);
            }
        }

        static void signed_int_print (signed long long i) {
            int_print<decltype(i)>(i);
        }

        static void unsigned_int_print (unsigned long long i) {
            int_print<decltype(i)>(i);
        }

        static void oct_print (unsigned long long o) {
            // u64, aka unsigned long long takes at most 22 octal symbols
            char octdigits[22u];
            std::uint8_t sz = 0u;
            if (o == 0) {
                octdigits[0] = '0';
                sz = 1;
            }
            while (o != 0) {
                octdigits[sz++] = static_cast<char>((o & 7) + 0x30);
                o >>= 3;
            }
            while (sz != 0u) {
                _putchar_lambda(octdigits[--sz]);
            }
        }

        static void hex_print (unsigned long long x, bool lowercase) {
            // u64, aka unsigned long long takes at most 16 hexadecimal symbols
            char hexdigits[16u];
            std::uint8_t sz = 0u;
            if (x == 0) {
                hexdigits[0] = '0';
                sz = 1;
            }
            while (x != 0) {
                auto num = x & 15;
                auto offs = (num <= 9) ? 0x30 : lowercase ? 0x57 : 0x37;
                hexdigits[sz++] = static_cast<char>(num + offs);
                x >>= 4;
            }
            while (sz != 0u) {
                _putchar_lambda(hexdigits[--sz]);
            }
        }

        static void hex_print_lowercase (unsigned long long x) {
            hex_print(x, true);
        }

        static void hex_print_uppercase (unsigned long long x) {
            hex_print(x, false);
        }

    public:
        static void _hhc (void* pmem) {
            (void)pmem;
        }
        static void __hc (void* pmem) {
            (void)pmem;
        }
        static void ___c (void* pmem) {
            using type = typename cspec::_t::___c;
            auto c = *reinterpret_cast<type*>(pmem);
            _putchar_lambda(c);
        }
        static void __lc (void* pmem) {
//            using type = typename cspec::_t::__lc;
            (void)pmem;
        }
        static void _llc (void* pmem) {
            (void)pmem;
        }
        static void _hhs (void* pmem) {
            (void)pmem;
        }
        static void __hs (void* pmem) {
            (void)pmem;
        }
        static void ___s (void* pmem) {
            using type = const typename cspec::_t::___s;
            auto s = *reinterpret_cast<type*>(pmem);
            while (*s != '\0') {
                _putchar_lambda(*s);
                ++s;
            }
        }
        static void __ls (void* pmem) {
//            using type = const typename cspec::_t::__ls;
            (void)pmem;
        }
        static void _lls (void* pmem) {
            (void)pmem;
        }
        static void _hhd (void* pmem) {
            using type = typename cspec::_t::_hhd;
            type tmp = *reinterpret_cast<type*>(pmem);
            signed_int_print(tmp);
        }
        static void __hd (void* pmem) {
            using type = typename cspec::_t::__hd;
            type tmp = *reinterpret_cast<type*>(pmem);
            signed_int_print(tmp);
        }
        static void ___d (void* pmem) {
            using type = typename cspec::_t::___d;
            type tmp = *reinterpret_cast<type*>(pmem);
            signed_int_print(tmp);
        }
        static void __ld (void* pmem) {
            using type = typename cspec::_t::__ld;
            type tmp = *reinterpret_cast<type*>(pmem);
            signed_int_print(tmp);
        }
        static void _lld (void* pmem) {
            using type = typename cspec::_t::_lld;
            type tmp = *reinterpret_cast<type*>(pmem);
            signed_int_print(tmp);
        }
        static void _hho (void* pmem) {
            using type = typename cspec::_t::_hho;
            type tmp = *reinterpret_cast<type*>(pmem);
            oct_print(tmp);
        }
        static void __ho (void* pmem) {
            using type = typename cspec::_t::__ho;
            type tmp = *reinterpret_cast<type*>(pmem);
            oct_print(tmp);
        }
        static void ___o (void* pmem) {
            using type = typename cspec::_t::___o;
            type tmp = *reinterpret_cast<type*>(pmem);
            oct_print(tmp);

        }
        static void __lo (void* pmem) {
            using type = typename cspec::_t::__lo;
            type tmp = *reinterpret_cast<type*>(pmem);
            oct_print(tmp);
        }
        static void _llo (void* pmem) {
            using type = typename cspec::_t::_llo;
            type tmp = *reinterpret_cast<type*>(pmem);
            oct_print(tmp);
        }
        static void _hhx (void* pmem) {
            using type = typename cspec::_t::_hhx;
            type tmp = *reinterpret_cast<type*>(pmem);
            hex_print_lowercase(tmp);
        }
        static void __hx (void* pmem) {
            using type = typename cspec::_t::__hx;
            type tmp = *reinterpret_cast<type*>(pmem);
            hex_print_lowercase(tmp);
        }
        static void ___x (void* pmem) {
            using type = typename cspec::_t::___x;
            type tmp = *reinterpret_cast<type*>(pmem);
            hex_print_lowercase(tmp);
        }
        static void __lx (void* pmem) {
            using type = typename cspec::_t::__lx;
            type tmp = *reinterpret_cast<type*>(pmem);
            hex_print_lowercase(tmp);
        }
        static void _llx (void* pmem) {
            using type = typename cspec::_t::_llx;
            type tmp = *reinterpret_cast<type*>(pmem);
            hex_print_lowercase(tmp);
        }
        static void _hhX (void* pmem) {
            using type = typename cspec::_t::_hhX;
            type tmp = *reinterpret_cast<type*>(pmem);
            hex_print_uppercase(tmp);
        }
        static void __hX (void* pmem) {
            using type = typename cspec::_t::__hX;
            type tmp = *reinterpret_cast<type*>(pmem);
            hex_print_uppercase(tmp);
        }
        static void ___X (void* pmem) {
            using type = typename cspec::_t::___X;
            type tmp = *reinterpret_cast<type*>(pmem);
            hex_print_uppercase(tmp);
        }
        static void __lX (void* pmem) {
            using type = typename cspec::_t::__lX;
            type tmp = *reinterpret_cast<type*>(pmem);
            hex_print_uppercase(tmp);
        }
        static void _llX (void* pmem) {
            using type = typename cspec::_t::_llX;
            type tmp = *reinterpret_cast<type*>(pmem);
            hex_print_uppercase(tmp);
        }
        static void _hhu (void* pmem) {
            using type = typename cspec::_t::_hhu;
            type tmp = *reinterpret_cast<type*>(pmem);
            unsigned_int_print(tmp);
        }
        static void __hu (void* pmem) {
            using type = typename cspec::_t::__hu;
            type tmp = *reinterpret_cast<type*>(pmem);
            unsigned_int_print(tmp);
        }
        static void ___u (void* pmem) {
            using type = typename cspec::_t::___u;
            type tmp = *reinterpret_cast<type*>(pmem);
            unsigned_int_print(tmp);
        }
        static void __lu (void* pmem) {
            using type = typename cspec::_t::__lu;
            type tmp = *reinterpret_cast<type*>(pmem);
            unsigned_int_print(tmp);
        }
        static void _llu (void* pmem) {
            using type = typename cspec::_t::_llu;
            type tmp = *reinterpret_cast<type*>(pmem);
            unsigned_int_print(tmp);
        }
    };
    // table of expected sizes to read from argument list when encountered specific token
    struct tables {
//        constexpr static const std::size_t* typesizes[conv_specs_cnt][length_mods_cnt] = {
//            //            hh,               h,            none,               l,              ll
//            {cspec::BitSize::_hhc, cspec::BitSize::__hc, cspec::BitSize::___c, cspec::BitSize::__lc, cspec::BitSize::_llc}, // c
//            {cspec::BitSize::_hhs, cspec::BitSize::__hs, cspec::BitSize::___s, cspec::BitSize::__ls, cspec::BitSize::_lls}, // s
//            {cspec::BitSize::_hhd, cspec::BitSize::__hd, cspec::BitSize::___d, cspec::BitSize::__ld, cspec::BitSize::_lld}, // d/i
//            {cspec::BitSize::_hho, cspec::BitSize::__ho, cspec::BitSize::___o, cspec::BitSize::__lo, cspec::BitSize::_llo}, // o
//            {cspec::BitSize::_hhx, cspec::BitSize::__hx, cspec::BitSize::___x, cspec::BitSize::__lx, cspec::BitSize::_llx}, // x
//            {cspec::BitSize::_hhX, cspec::BitSize::__hX, cspec::BitSize::___X, cspec::BitSize::__lX, cspec::BitSize::_llX}, // X
//            {cspec::BitSize::_hhu, cspec::BitSize::__hu, cspec::BitSize::___u, cspec::BitSize::__lu, cspec::BitSize::_llu}, // u
//        };
        constexpr static const fpwrout_t writeouts[_conv_specs_cnt][_length_mods_cnt] {
            //            hh,               h,            none,               l,              ll
            {wroutimpl::_hhc, wroutimpl::__hc, wroutimpl::___c, wroutimpl::__lc, wroutimpl::_llc}, // c
            {wroutimpl::_hhs, wroutimpl::__hs, wroutimpl::___s, wroutimpl::__ls, wroutimpl::_lls}, // s
            {wroutimpl::_hhd, wroutimpl::__hd, wroutimpl::___d, wroutimpl::__ld, wroutimpl::_lld}, // d/i
            {wroutimpl::_hho, wroutimpl::__ho, wroutimpl::___o, wroutimpl::__lo, wroutimpl::_llo}, // o
            {wroutimpl::_hhx, wroutimpl::__hx, wroutimpl::___x, wroutimpl::__lx, wroutimpl::_llx}, // x
            {wroutimpl::_hhX, wroutimpl::__hX, wroutimpl::___X, wroutimpl::__lX, wroutimpl::_llX}, // X
            {wroutimpl::_hhu, wroutimpl::__hu, wroutimpl::___u, wroutimpl::__lu, wroutimpl::_llu}, // u
        };
        // indices for the table above
        struct idx {
            struct cvsp {
                constexpr static const auto c = 0u;
                constexpr static const auto s = 1u;
                constexpr static const auto d = 2u; // 'i'
                constexpr static const auto o = 3u;
                constexpr static const auto x = 4u;
                constexpr static const auto X = 5u;
                constexpr static const auto u = 6u;
                // alias
                constexpr static const auto i = d;
                // end
                constexpr static const auto end = _conv_specs_cnt;
                // none
                constexpr static const auto _ = _conv_specs_cnt + 1u;
            };
            struct lmod {
                constexpr static const auto _hh = 0u;
                constexpr static const auto __h = 1u;
                constexpr static const auto ___ = 2u; // 'none'
                constexpr static const auto __l = 3u;
                constexpr static const auto _ll = 4u;
                // end
                constexpr static const auto end = _length_mods_cnt;
            };
            // indications of which indices holders to be used as rows or columns
            using row = cvsp;
            using col = lmod;
        };
    };

private:
    static std::size_t parse_length_mod (const char* next, std::size_t& offs) noexcept {
        auto c0 = next[0u];
        auto c1 = next[1u];

        ++offs;
        if ((c0 == 'h') && (c1 != 'h')) {
            return tables::idx::lmod::__h;
        } else if (c1 == 'h') {
            ++offs;
            return tables::idx::lmod::_hh;
        } else if ((c0 == 'l') && (c1 != 'l')) {
            return tables::idx::lmod::__l;
        } else if (c1 == 'l') {
            ++offs;
            return tables::idx::lmod::_ll;
        }
        --offs;
        return tables::idx::lmod::___;
    }

    static std::size_t parse_conv_spec (const char* next, std::size_t& offs) noexcept {
        auto c0 = next[0u];

        ++offs;
        if (c0 == 'c') {
            return tables::idx::cvsp::c;
        }else if (c0 == 's') {
            return tables::idx::cvsp::s;
        } else if ((c0 == 'd') || (c0 == 'i')) {
            return tables::idx::cvsp::d;
        } else if (c0 == 'o') {
            return tables::idx::cvsp::o;
        } else if (c0 == 'x') {
            return tables::idx::cvsp::x;
        } else if (c0 == 'X') {
            return tables::idx::cvsp::X;
        } else if (c0 == 'u') {
            return tables::idx::cvsp::u;
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
        return tables::idx::cvsp::_;
    }

    // parse the symbol next after the first '%' (see the use in printf_light below)
    static std::size_t parse_argtok (const char* next, std::size_t& lmodout, std::size_t& cspecout) noexcept {
        std::size_t offs = 0u;
        lmodout  = parse_length_mod(next, offs);
        cspecout = parse_conv_spec(&next[offs], offs);
        return offs;
    }

private:
    template <typename T>
    static std::size_t process_va_list_helper (void* pbigstorage, std::va_list& arglist) {
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
    // I could possibly create some virtual wrappers around the natives, but that's just waaaaay more overhead.
    //
    static std::size_t process_va_list (void* pbigmemz, std::va_list& arglist, std::size_t cvsp, std::size_t lmod) {
        using idxcvsp = typename tables::idx::cvsp;
        using idxlmod = typename tables::idx::lmod;

        if ((cvsp == idxcvsp::c) && (lmod == idxlmod::___)) { // no modifiers for chars
            return process_va_list_helper<int>(pbigmemz, arglist); // char is promoted to int when passed to va_list
        } else if ((cvsp == idxcvsp::s) && (lmod == idxlmod::___)) { // no modifiers for strings
            return process_va_list_helper<const char*>(pbigmemz, arglist);
        } else if (cvsp == idxcvsp::d) {
            // signed char, short are promoted to int when passed to va_list
            if ((lmod == idxlmod::_hh) || (lmod == idxlmod::__h)) {
                return process_va_list_helper<int>(pbigmemz, arglist);
            } else if (lmod == idxlmod::___) {
                return process_va_list_helper<int>(pbigmemz, arglist);
            } else if (lmod == idxlmod::__l) {
                return process_va_list_helper<long>(pbigmemz, arglist);
            } else if (lmod == idxlmod::_ll) {
                return process_va_list_helper<long long>(pbigmemz, arglist);
            }
        } else if ((cvsp == idxcvsp::o) || (cvsp == idxcvsp::x) || (cvsp == idxcvsp::X) || (cvsp == idxcvsp::u)) {
            // unsigned char, unsigned short are promoted to int when passed to va_list
            if ((lmod == idxlmod::_hh) || (lmod == idxlmod::__h)) {
                return process_va_list_helper<int>(pbigmemz, arglist);
            } else if (lmod == idxlmod::___) {
                return process_va_list_helper<unsigned int>(pbigmemz, arglist);
            } else if (lmod == idxlmod::__l) {
                return process_va_list_helper<unsigned long>(pbigmemz, arglist);
            } else if (lmod == idxlmod::_ll) {
                return process_va_list_helper<unsigned long long>(pbigmemz, arglist);
            }
        }

//        cvsp = idxcvsp::_;
//        lmod = idxlmod::___;

        return 0u;
    }
    
private:
    enum class op : std::uint8_t {
        brk, cnt, nop
    };
    
    [[nodiscard]]
    static auto process_char_pointer (
        const char* &p, std::va_list& arglist, std::size_t& i
    ) -> op {
        auto c0 = p[i];
        if (c0 == '\0') {
            return op::brk; ///< break
        } else if (c0 == '%') {
            if (i + 1u >= maxfmtlen)
                return op::brk; ///< break
            if (p[i + 1u] == '\0')
                return op::brk; ///< break
        
            std::size_t lmod;
            std::size_t cvsp;
            std::size_t j = i + 1u; // save i + 1u
            i += parse_argtok(&p[i + 1u], lmod, cvsp);
        
            // if no valid conversion specifier was found
            // print out th
            if (cvsp == tables::idx::cvsp::_) {
                _putchar_lambda(c0);
                for (; j < i + 1u; ++j) {
                    _putchar_lambda(p[j]);
                }
                return op::cnt; ///< continue
            }
        
            using biggest_native_type = long double;
            std::uint8_t magic_memory[sizeof(biggest_native_type)] {0};
            auto p_magic_memory = reinterpret_cast<void*>(&magic_memory);
            /*auto typesz =*/ process_va_list(p_magic_memory, arglist, cvsp, lmod);
            tables::writeouts[cvsp][lmod](p_magic_memory);
        } else {
            _putchar_lambda(c0);
        }
        return op::nop;
    }
    
public:
    auto printf (const char* fmt, ...) const noexcept -> void {
        std::va_list arglist;
        va_start(arglist, fmt);
        printf_light::vprintf(fmt, arglist);
        va_end(arglist);
    }

    auto vprintf (const char* fmt, std::va_list& arglist) const noexcept
    -> void {
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
};

}

}

#endif /// KCPPT_PRINTS_PRINTF_LIGHT_HPP
