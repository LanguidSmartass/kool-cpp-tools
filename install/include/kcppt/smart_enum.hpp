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

#include <string_view>

namespace kcppt::smart_enum {

template <typename T>
class smart_enum {
private:
    using self_type = smart_enum<T>;
    
protected:
    enum class underlying : T {};
    
    underlying m_t;
    
public:
    constexpr explicit smart_enum (T t) noexcept :
    m_t(static_cast<underlying>(t))
    {}
    
    [[nodiscard]] constexpr auto value () const noexcept {
        return static_cast<T>(m_t);
    }
    
    constexpr auto operator== (self_type other) const noexcept {
        return m_t == other.m_t;
    }
    
    constexpr auto operator!= (self_type other) const noexcept {
        return m_t != other.m_t;
    }
};

template <typename T, typename CharT>
class smart_enum_named : public smart_enum<T> {
private:
    using base = smart_enum<T>;
    using self_type = smart_enum_named<T, CharT>;
    using s_view = std::basic_string_view<CharT>;
    
protected:
    const s_view m_s;
    
public:
    constexpr explicit
    smart_enum_named (T t, s_view s) noexcept :
        base {t},
        m_s{s}
    {}
    
    [[nodiscard]] constexpr auto name () const noexcept {
        return s_view{m_s};
    }
    
    constexpr auto operator== (const self_type& other) const noexcept {
        return (base::m_t == other.m_t) && (m_s == other.m_s);
    }
    
    constexpr auto operator!= (const self_type& other) const noexcept {
        return (base::m_t != other.m_t) || (m_s == other.m_s);
    }
};

template <typename T, typename CharT>
smart_enum_named (T t, const CharT* s) ->
smart_enum_named<T, typename std::basic_string_view<CharT>::value_type>;

}

#endif /// KCPPT_SENUM_HPP
