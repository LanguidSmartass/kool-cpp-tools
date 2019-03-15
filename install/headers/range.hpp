/** @file range.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   05.03.2019
 * 
 * @brief  
 * 
 */

#ifndef KCPPT_RANGE_HPP
#define KCPPT_RANGE_HPP

#include <cinttypes>
#include <utility>

namespace kcppt {

namespace range {

template <typename T, typename F>
class [[nodiscard]] iterator {
private:
    T _i;
    T _step;
    
private:
    friend F;
    constexpr explicit iterator (T i, T step = 1) noexcept :
    _i(i), _step(step)
    {}

public:
    constexpr auto operator++ () noexcept -> iterator& {
        _i += _step;
        return *this;
    }
    
    [[nodiscard]]
    constexpr auto operator!= (const iterator& other) noexcept -> bool {
        return _i != other._i;
    }
    
    [[nodiscard]]
    constexpr auto operator* () noexcept -> T {
        return _i;
    }
};

/**
 * @brief A class that acts akin to Python3's 'range()' built-in function.
 *        Use in 'range for loop' expressions.
 *        Examples:
 *        'for (auto i = 0u; i < value; ++i) {}' becomes
 *        'for (auto i : range(value)) {}'
 *        or
 *        'for (auto i = -15u; i < 3; i += 5) {}' becomes
 *        'for (auto i : range(-15, 3, 5)) {}'
 *
 * @tparam T -- deduced integral type for range values
 *
 */
template <typename T>
class [[nodiscard]] range {
    static_assert(std::is_integral_v<T>);
private:
    using iterator = iterator<T, range>;
    
private:
    T _ibegin;
    T _iend;
    T _istep;
    
public:
    explicit constexpr range (T i) noexcept : _ibegin(0), _iend(i), _istep(1) {
        if (_iend < 0) {
            _ibegin = _iend;
            _iend = 0;
        }
    }
    
    template <typename T1, typename T2 = int>
    constexpr range (T ibegin, T1 iend, T2 istep = 1) noexcept :
    _ibegin(ibegin), _iend(iend), _istep(istep)
    {}

public:
    [[nodiscard]]
    constexpr auto begin () const noexcept -> iterator {
        return iterator(_ibegin, _istep);
    }
    
    [[nodiscard]]
    constexpr auto end () const noexcept -> iterator {
        return iterator(_iend, _istep);
    }
    
};

/**
 * @brief Take any container with methon 'size()' (or a built-in array)
 *        and return an iterable list of indices of this container's elements.
 *        Use in range-for loop expressions, like:
 *        std::vector v {13, 14, 15, 16};
 *
 *        'for (auto i = 0; i < v.end() - v.begin(); ++i) {}' becomes
 *        'for (auto i : indices(v)) {}'
 *
 *        'for (auto i = 3; i < v.end() - v.begin(); i += 4) {}' becomes
 *        'for (auto i : indices(v, 3, 4)) {}'
 *
 */
class [[nodiscard]] indices {
private:
    using iterator = iterator<std::size_t, indices>;
    
    template <typename T, std::size_t Sz>
    using pod_array = T[Sz];
    
private:
    std::size_t _ibegin;
    std::size_t _iend;
    std::size_t _istep;

public:
    template <typename C> //, typename = std::enable_if_t<!std::is_array_v<C>>>
    explicit constexpr indices (
        const C& c, std::size_t begin = 0u, std::size_t step = 1u
    ) noexcept :
        _ibegin(begin), _iend(c.size()), _istep(step)
    {}
    
    template <typename T, std::size_t Sz>
    explicit constexpr indices (
        const pod_array<T, Sz>& a, std::size_t begin = 0u, std::size_t step = 1u
    ) noexcept :
        _ibegin(begin), _iend(Sz), _istep(step)
    {}

public:
    [[nodiscard]]
    constexpr auto begin () const noexcept -> iterator {
        return iterator(_ibegin, _istep);
    }
    
    [[nodiscard]]
    constexpr auto end () const noexcept -> iterator {
        return iterator(_iend, _istep);
    }

};

}

}

#endif /// KCPPT_RANGE_HPP
