/** @file range.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   05.03.2019
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

#ifndef KCPPT_RANGE_HPP
#define KCPPT_RANGE_HPP

#include <cinttypes>
#include <utility>

namespace kcppt {

namespace range {

template <typename...Ts>
struct largest_type;

//template <typename T0, typename...Ts>
//struct largest_type<T0, Ts...> {
//    using type = typename largest_type<Ts...>::type;
//};

template <typename T0, typename T1>
struct largest_type<T0, T1> {
    using type = std::conditional_t<
        sizeof(T0) >= sizeof(T1)
        , T0
        , T1
    >;
};

template <typename...Ts>
using largest_type_t = typename largest_type<Ts...>::type;

template <typename T, typename F>
class [[nodiscard]] iterator {
private:
    T m_i;
    T m_step;
    
private:
    friend F;
    constexpr explicit iterator (T i, T step = 1) noexcept :
        m_i(i), m_step(step)
    {}

public:
    constexpr auto operator++ () noexcept -> iterator& {
        m_i += m_step;
        return *this;
    }
    
    [[nodiscard]]
    constexpr auto operator!= (const iterator& other) noexcept -> bool {
        /// '<' instead of '!=' is intentional,
        /// otherwise in cases when _step is > 1 range-for loop can
        /// go past the last index of some container
        return m_i < other.m_i;
    }
    
    [[nodiscard]]
    constexpr auto operator<= (const iterator& other) noexcept -> bool {
        return m_i <= other.m_i;
    }
    
    [[nodiscard]]
    constexpr auto operator- (const iterator& other) noexcept -> T {
        return m_i - other.m_i;
    }
    
    [[nodiscard]]
    constexpr auto operator* () noexcept -> T {
        return m_i;
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
    T m_ibegin;
    T m_iend;
    T m_istep;
    
public:
    explicit constexpr range (T i) noexcept : m_ibegin(0), m_iend(i), m_istep(1) {
        if (m_iend < 0) {
            m_ibegin = m_iend;
            m_iend = 0;
        }
    }
    
    template <typename T1, typename T2 = T1>
    constexpr range (T ibegin, T1 iend, T2 istep = T2 { 1 }) noexcept :
    m_ibegin { ibegin }
    , m_iend { iend }
    , m_istep { istep }
    {}
    
public:
    [[nodiscard]]
    constexpr auto begin () const noexcept -> iterator {
        return iterator(m_ibegin, m_istep);
    }
    
    [[nodiscard]]
    constexpr auto end () const noexcept -> iterator {
        return iterator(m_iend, m_istep);
    }
    
    [[nodiscard]]
    constexpr auto step () const noexcept -> T {
        return m_istep;
    }
};

template <typename T0, typename T1, typename T2 = T1>
range (T0 ibegin, T1 iend, T2 istep = T2 { 1 }) -> range<largest_type_t<T0, T1>>;
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
    std::size_t m_ibegin;
    std::size_t m_iend;
    std::size_t m_istep;

public:
    template <typename C> //, typename = std::enable_if_t<!std::is_array_v<C>>>
    explicit constexpr indices (
        const C& c, std::size_t begin = 0u, std::size_t step = 1u
    ) noexcept :
        m_ibegin(begin), m_iend(c.size()), m_istep(step)
    {}
    
    template <typename T, std::size_t Sz>
    explicit constexpr indices (
        const pod_array<T, Sz>& a, std::size_t begin = 0u, std::size_t step = 1u
    ) noexcept :
        m_ibegin(begin), m_iend(Sz), m_istep(step)
    {}

public:
    [[nodiscard]]
    constexpr auto begin () const noexcept -> iterator {
        return iterator(m_ibegin, m_istep);
    }
    
    [[nodiscard]]
    constexpr auto end () const noexcept -> iterator {
        return iterator(m_iend, m_istep);
    }

};

}

}

#endif /// KCPPT_RANGE_HPP
