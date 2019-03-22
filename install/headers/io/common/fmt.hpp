/** @file prifmt.hpp
 *
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   17.01.2019
 *
 * @brief
 *
 */

#ifndef KCPPT_IO_FMT_HPP
#define KCPPT_IO_FMT_HPP

#include "../pow2.hpp"
#include <cinttypes>
#include <type_traits>
#include <climits>

namespace kcppt {

namespace io {

namespace fmt {

struct by_size {
private:
    template <std::size_t sz>
    struct is_valid_size {
        static_assert(sizeof(char) * 8 == CHAR_BIT, "char must be 8 bits long");
        static_assert(
            sz > sizeof(std::uintmax_t),
            "Provided size is too big for this system"
        );
        static_assert(
            pow2::is_pow2(sz),
            "Provided size must be a power of 2"
        );
    };

public:
    constexpr static const char* udec_f (std::size_t sz) noexcept {
        return (sz == 1) ? "%" PRIu8 :
               (sz == 2) ? "%" PRIu16 :
               (sz == 4) ? "%" PRIu32 :
               (sz == 8) ? "%" PRIu64 :
               (sz == sizeof(std::uintmax_t)) ? "%" PRIuMAX : nullptr;
    }
    
    constexpr static const char* sdec_f (std::size_t sz) noexcept {
        return (sz == 1) ? "%" PRIi8 :
               (sz == 2) ? "%" PRIi16 :
               (sz == 4) ? "%" PRIi32 :
               (sz == 8) ? "%" PRIi64 :
               (sz == sizeof(std::intmax_t)) ? "%" PRIiMAX : nullptr;
    }
    
    constexpr static const char* oct_f (std::size_t sz) noexcept {
        return (sz == 1) ? "%" PRIo8 :
               (sz == 2) ? "%" PRIo16 :
               (sz == 4) ? "%" PRIo32 :
               (sz == 8) ? "%" PRIo64 :
               (sz == sizeof(std::uintmax_t)) ? "%" PRIoMAX : nullptr;
    }
    
    constexpr static const char* hex_f (std::size_t sz) noexcept {
        return (sz == 1) ? "%" PRIx8 :
               (sz == 2) ? "%" PRIx16 :
               (sz == 4) ? "%" PRIx32 :
               (sz == 8) ? "%" PRIx64 :
               (sz == sizeof(std::uintmax_t)) ? "%" PRIxMAX : nullptr;
    }
    
    constexpr static const char* HEX_f (std::size_t sz) noexcept {
        return (sz == 1) ? "%" PRIX8 :
               (sz == 2) ? "%" PRIX16 :
               (sz == 4) ? "%" PRIX32 :
               (sz == 8) ? "%" PRIX64 :
               (sz == sizeof(std::uintmax_t)) ? "%" PRIXMAX : nullptr;
    }
    
    template <std::size_t sz>
    constexpr static const char* udec_f () noexcept {
        return udec_f(sz);
    }
    
    template <std::size_t sz>
    constexpr static const char* sdec_f () noexcept {
        return sdec_f(sz);
    }
    
    template <std::size_t sz>
    constexpr static const char* oct_f () noexcept {
        return oct_f(sz);
    }
    
    template <std::size_t sz>
    constexpr static const char* hex_f () noexcept {
        return hex_f(sz);
    }
    
    template <std::size_t sz>
    constexpr static const char* HEX_f () noexcept {
        return HEX_f(sz);
    }
    
    template <std::size_t sz = sizeof(unsigned int)>
    struct udec {
    private:
        using check = is_valid_size<sz>;
    
    public:
        constexpr static const char* value = udec_f<sz>();
    };
    
    template <std::size_t sz = sizeof(int)>
    struct sdec {
    private:
        using check = is_valid_size<sz>;
    
    public:
        constexpr static const char* value = sdec_f<sz>();
    };
    
    template <std::size_t sz = sizeof(unsigned int)>
    struct oct {
    private:
        using check = is_valid_size<sz>;
    
    public:
        constexpr static const char* value = oct_f<sz>();
    };
    
    template <std::size_t sz = sizeof(unsigned int)>
    struct hex {
    private:
        using check = is_valid_size<sz>;
    
    public:
        constexpr static const char* value = hex_f<sz>();
    };
    
    template <std::size_t sz = sizeof(unsigned int)>
    struct HEX {
    private:
        using check = is_valid_size<sz>;
    
    public:
        constexpr static const char* value = HEX_f<sz>();
    };
};

struct by_type {
private:
    template <typename T>
    constexpr static auto is_signed_or_pointer =
        std::is_signed_v<T> || std::is_pointer_v<T>;
    template <typename T>
    constexpr static auto is_unsigned_or_pointer =
        std::is_unsigned_v<T> || std::is_pointer_v<T>;
    template <typename T>
    constexpr static auto is_integral_or_pointer =
        std::is_integral_v<T> || std::is_pointer_v<T>;
    
public:
    template <typename T>
    constexpr static const char* udec_f () noexcept {
        static_assert(is_unsigned_or_pointer<T>);
        return by_size::udec_f<sizeof(T)>();
    }
    
    template <typename T>
    constexpr static const char* sdec_f () noexcept {
        static_assert(is_signed_or_pointer<T>);
        return by_size::sdec_f<sizeof(T)>();
    }
    
    template <typename T>
    constexpr static const char* oct_f () noexcept {
        static_assert(is_integral_or_pointer<T>);
        return by_size::oct_f<sizeof(T)>();
    }
    
    template <typename T>
    constexpr static const char* hex_f () noexcept {
        static_assert(is_integral_or_pointer<T>);
        return by_size::hex_f<sizeof(T)>();
    }
    
    template <typename T>
    constexpr static const char* HEX_f () noexcept {
        static_assert(is_integral_or_pointer<T>);
        return by_size::HEX_f<sizeof(T)>();
    }
    
    template <typename T>
    struct udec {
        constexpr static const char* value = udec_f<T>();
    };
    
    template <typename T>
    struct sdec {
        constexpr static const char* value = sdec_f<T>();
    };
    
    template <typename T>
    struct oct {
        constexpr static const char* value = oct_f<T>();
    };
    
    template <typename T>
    struct hex {
        constexpr static const char* value = hex_f<T>();
    };
    
    template <typename T>
    struct HEX {
        constexpr static const char* value = HEX_f<T>();
    };
};

struct ptr_udec {
    constexpr static const char* value = "%" PRIuPTR;
};

struct ptr_sdec {
    constexpr static const char* value = "%" PRIiPTR;
};

struct ptr_oct {
    constexpr static const char* value = "%" PRIoPTR;
};

struct ptr_hex {
    constexpr static const char* value = "%" PRIxPTR;
};

struct ptr_HEX {
    constexpr static const char* value = "%" PRIXPTR;
};

constexpr static const char* ptr_udec_f () noexcept { return ptr_udec::value; }

constexpr static const char* ptr_sdec_f () noexcept { return ptr_sdec::value; }

constexpr static const char* ptr_oct_f () noexcept { return ptr_oct::value; }

constexpr static const char* ptr_hex_f () noexcept { return ptr_hex::value; }

constexpr static const char* ptr_HEX_f () noexcept { return ptr_HEX::value; }

} // namespace fmt

} // namespace io

} // namespace kcppt

#endif /// KCPPT_IO_FMT_HPP
