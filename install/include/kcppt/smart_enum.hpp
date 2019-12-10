/** @file senum.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   24.09.2019
 * 
 * @brief  smart enum
 * 
 */

#ifndef KCPPT_SMART_ENUM_HPP
#define KCPPT_SMART_ENUM_HPP

#include <cstdlib>
#include <string_view>

namespace kcppt::smart_enum {

template <typename T>
class smart_enum {
private:
    constexpr static auto _sm_is_int = std::is_integral_v<T>;
    constexpr static auto _sm_is_flt = std::is_floating_point_v<T>;
    
    static_assert(_sm_is_int || _sm_is_flt);
    
    using self_type = smart_enum<T>;
    using enable_if_int = std::enable_if_t<_sm_is_int>;
    using enable_if_flt = std::enable_if_t<_sm_is_flt>;
    
protected:
    T _m_t;
    
    [[nodiscard]] constexpr auto compare (T other_t) const noexcept {
        auto this_t = _m_t;
        if constexpr (_sm_is_int) {
            return this_t == other_t;
        } else if constexpr (_sm_is_flt) {
            constexpr auto e = std::numeric_limits<T>::epsilon();
            // auto diff = _m_t > other_m_t ? (_m_t - other_m_t) : (other_m_t - _m_t);
            auto diff = std::abs(this_t - other_t);
            return diff <= e;
        }
    }
    
public:
    constexpr explicit smart_enum (T t) noexcept :
        _m_t(t)
    {}
    
    [[nodiscard]] constexpr auto value () const noexcept {
        return _m_t;
    }
    
    constexpr auto operator= (smart_enum other) noexcept -> smart_enum& {
        _m_t = other._m_t;
        return *this;
    }
    
    [[nodiscard]] constexpr auto operator== (smart_enum other) const noexcept {
        return compare(other._m_t);
    }
    
    [[nodiscard]] constexpr auto operator!= (smart_enum other) const noexcept {
        return !(*this == other);
    }
};

template <typename T, typename CharT>
class smart_enum_named : public smart_enum<T> {
private:
    using base = smart_enum<T>;
    using self_type = smart_enum_named<T, CharT>;
    
public:
    using s_view = std::basic_string_view<CharT>;
    
protected:
    s_view _m_s;
    
public:
    constexpr explicit
    smart_enum_named (T t, s_view s) noexcept :
        base {t},
        _m_s{s}
    {}
    
    [[nodiscard]] constexpr auto name () const noexcept {
        return s_view{_m_s};
    }
    
    constexpr auto operator= (smart_enum_named other) noexcept -> smart_enum_named& {
        base::_m_t = other._m_t;
        _m_s = other._m_s;
        return *this;
    }
    
    [[nodiscard]] constexpr auto operator== (const self_type& other) const noexcept {
        return base::compare(other._m_t) && (_m_s == other._m_s);
    }
    
    [[nodiscard]] constexpr auto operator!= (const self_type& other) const noexcept {
        return !(*this == other);
    }
};

template <typename T, typename CharT>
smart_enum_named (T t, const CharT* s) ->
smart_enum_named<T, typename std::basic_string_view<CharT>::value_type>;

}

#endif /// KCPPT_SENUM_HPP
