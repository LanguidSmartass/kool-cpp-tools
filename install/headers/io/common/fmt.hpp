/** @file prifmt.hpp
 *
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   17.01.2019
 *
 * @brief
 *
 */

#ifndef KCPPT_IO_COMMON_FMT_HPP
#define KCPPT_IO_COMMON_FMT_HPP

#include "../../pow2.hpp"
#include "../../traits.hpp"
#include <cinttypes>
#include <type_traits>
#include <climits>

namespace kcppt {

namespace io {

namespace common {

namespace fmt {

namespace out {

namespace ascii {

}

namespace integrals {

struct by_size {
private:
    template <std::size_t Sz>
    struct is_valid_size {
        static_assert(sizeof(char) * 8 == CHAR_BIT, "char must be 8 bits long");
        constexpr static bool value = pow2::is_pow2(Sz);
    };
    
    template <std::size_t Sz>
    constexpr static auto is_valid_size_v = is_valid_size<Sz>::value;
    
public:
    constexpr static auto udec_f (std::size_t sz) noexcept -> const char* {
        return (sz == 1) ? "%" PRIu8 :
               (sz == 2) ? "%" PRIu16 :
               (sz == 4) ? "%" PRIu32 :
               (sz == 8) ? "%" PRIu64 :
               (sz == sizeof(std::uintmax_t)) ? "%" PRIuMAX : nullptr;
    }
    
    constexpr static auto sdec_f (std::size_t sz) noexcept -> const char* {
        return (sz == 1) ? "%" PRIi8 :
               (sz == 2) ? "%" PRIi16 :
               (sz == 4) ? "%" PRIi32 :
               (sz == 8) ? "%" PRIi64 :
               (sz == sizeof(std::intmax_t)) ? "%" PRIiMAX : nullptr;
    }
    
    constexpr static auto oct_f (std::size_t sz) noexcept -> const char* {
        return (sz == 1) ? "%" PRIo8 :
               (sz == 2) ? "%" PRIo16 :
               (sz == 4) ? "%" PRIo32 :
               (sz == 8) ? "%" PRIo64 :
               (sz == sizeof(std::uintmax_t)) ? "%" PRIoMAX : nullptr;
    }
    
    constexpr static auto hex_f (std::size_t sz) noexcept -> const char* {
        return (sz == 1) ? "%" PRIx8 :
               (sz == 2) ? "%" PRIx16 :
               (sz == 4) ? "%" PRIx32 :
               (sz == 8) ? "%" PRIx64 :
               (sz == sizeof(std::uintmax_t)) ? "%" PRIxMAX : nullptr;
    }
    
    constexpr static auto HEX_f (std::size_t sz) noexcept -> const char* {
        return (sz == 1) ? "%" PRIX8 :
               (sz == 2) ? "%" PRIX16 :
               (sz == 4) ? "%" PRIX32 :
               (sz == 8) ? "%" PRIX64 :
               (sz == sizeof(std::uintmax_t)) ? "%" PRIXMAX : nullptr;
    }
    
    template <std::size_t sz>
    constexpr static auto udec_v = udec_f(sz);
    
    template <std::size_t sz>
    constexpr static auto sdec_v = sdec_f(sz);
    
    template <std::size_t sz>
    constexpr static auto oct_v = oct_f(sz);
    
    template <std::size_t sz>
    constexpr static auto hex_v = hex_f(sz);
    
    template <std::size_t sz>
    constexpr static auto HEX_v = HEX_f(sz);
    
};

struct by_type {
private:
    template <typename T>
    constexpr static auto is_integral_or_pointer =
        traits::is_integral_or_pointer_v<T>;
    
public:
    template <typename T>
    struct udec {
        static_assert(is_integral_or_pointer<T>);
        constexpr static auto value = by_size::udec_v<sizeof(T)>;
    };
    
    template <typename T>
    struct sdec {
        static_assert(is_integral_or_pointer<T>);
        constexpr static auto value = by_size::sdec_v<sizeof(T)>;
    };
    
    template <typename T>
    struct oct {
        static_assert(is_integral_or_pointer<T>);
        constexpr static auto value = by_size::oct_v<sizeof(T)>;
    };
    
    template <typename T>
    struct hex {
        static_assert(is_integral_or_pointer<T>);
        constexpr static auto value = by_size::hex_v<sizeof(T)>;
    };
    
    template <typename T>
    struct HEX {
        static_assert(is_integral_or_pointer<T>);
        constexpr static auto value = by_size::HEX_v<sizeof(T)>;
    };
    
    template <typename T>
    constexpr static auto udec_v = udec<T>::value;
    
    template <typename T>
    constexpr static auto sdec_v = sdec<T>::value;
    
    template <typename T>
    constexpr static auto oct_v = oct<T>::value;
    
    template <typename T>
    constexpr static auto hex_v = hex<T>::value;
    
    template <typename T>
    constexpr static auto HEX_v = HEX<T>::value;
    
};

struct ptr {
    constexpr static auto udec_v = "%" PRIuPTR;
    constexpr static auto sdec_v = "%" PRIiPTR;
    constexpr static auto oct_v = "%" PRIoPTR;
    constexpr static auto hex_v = "%" PRIxPTR;
    constexpr static auto HEX_v = "%" PRIXPTR;
};

}

namespace floats {

}

}

}

}

}

}

#endif /// KCPPT_IO_COMMON_FMT_HPP