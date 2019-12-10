/** @file byte.hpp
 *
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   13.07.2019
 *
 */
#ifndef KCPPT_RATE_HPP
#define KCPPT_RATE_HPP

#include <chrono>

namespace kcppt {

namespace rate {
/**
 * @brief Framerate, bitrate, speed -- you name it
 * @tparam std::duration
 * @tparam Disambiguator int
 */
template <class Duration, typename Value = std::size_t, std::size_t Disambiguator = 0>
class rate {
protected:
    using repr  = typename Duration::rep;
    using ratio = typename Duration::period;
    constexpr static auto numer = ratio::num;
    constexpr static auto denom = ratio::den;
    
    static_assert(std::is_same_v<Duration, std::chrono::duration<repr, ratio>>);
    
    Value    m_value;
    Duration m_duration;

public:
    explicit
    constexpr rate (Value const& v, Duration const& d = Duration {1}) :
        m_value{v}
        , m_duration{d}
    {}
    
    constexpr auto value () const noexcept { return m_value; }
    
    constexpr auto duration () const noexcept { return m_duration; }
    
    /**
     * @brief number of seconds per one element (one element duration)
     * @tparam Prc
     * @param p
     * @return
     */
    template <typename Prc = repr>
    constexpr auto spe ([[maybe_unused]] Prc p = {}) const noexcept -> Prc {
        return raw_value<std::chrono::seconds, Prc>();
    }
    /**
     * @brief calculate resulting numerator to integral or floating point
     * @tparam Prc
     * @param p
     * @return
     */
    template <typename Prc = repr>
    constexpr auto numerator ([[maybe_unused]] Prc p = {}) const noexcept -> Prc {
        return static_cast<Prc>(m_value) * denom;
    }
    /**
     * @brief calculate resulting denominator to integral or floating point
     * @tparam Prc
     * @param p
     * @return
     */
    template <typename Prc = repr>
    constexpr auto denominator ([[maybe_unused]] Prc p = {}) const noexcept -> Prc {
        return static_cast<Prc>(numer) * m_duration.count();
    }
    /**
     * @brief calculate resulting rate value (per second) to integral or floating point
     * @tparam Prc
     * @param p
     * @return
     */
    template <typename Prc = repr>
    constexpr auto raw_value ([[maybe_unused]] Prc p = {}) const noexcept -> Prc {
        return numerator<Prc>() / denominator<Prc>();
    }
    /**
     * @brief Convert value to other duration
     * @tparam OtherDur other duration, for example std::chrono::milliseconds
     * @tparam Prc template-parameter style precision specification, like f<double>().
     *             Defaults to 'repr'
     * @param p function-parameter style precision specification, like f(double{}).
     *             Defaults to 'repr{}'
     * @return units of type 'Prc', but in other duration
     */
    template <typename OtherDur, typename Prc = repr>
    constexpr auto raw_value ([[maybe_unused]] Prc p = {}) const noexcept {
        return (numerator<Prc>() * OtherDur::period::den) / (denominator<Prc>() * OtherDur::period::num);
    }
    
    template <typename Prc = repr>
    constexpr auto operator/ (Prc const d) const noexcept {
        auto v = static_cast<Prc>(m_value) / d;
        return rate { v, m_duration };
    }
    
    template <typename Prc = repr>
    constexpr auto operator* (Prc const d) const noexcept {
        auto v = static_cast<Prc>(m_value) * d;
        return rate { v, m_duration };
    }
    
};

using fps = rate<std::chrono::seconds, std::size_t, 0>;
using bps = rate<std::chrono::seconds, std::size_t, 1>;

using Hz  = rate<std::chrono::seconds, std::size_t, 2>;
using kHz = rate<std::chrono::milliseconds, std::size_t, 2>;
using MHz = rate<std::chrono::microseconds, std::size_t, 2>;
using GHz = rate<std::chrono::nanoseconds, std::size_t,  2>;

}

namespace rate_operators {

template <class D, class V, std::size_t N, class Rep, class Ratio>
constexpr inline auto operator* (
    std::chrono::duration<Rep, Ratio> const& other_d, rate::rate<D, V, N> const& rt
) noexcept -> std::size_t {
    auto const num = other_d.count() * Ratio::num * rt.numerator();
    auto const den = Ratio::den * rt.denominator();
    return num / den;
}

template <class D, class V, std::size_t N, class Rep, class Ratio>
constexpr inline auto operator* (
    rate::rate<D, V, N> const& rt, std::chrono::duration<Rep, Ratio> const& other_d
) noexcept -> std::size_t {
    return operator*(other_d, rt);
}

template <class D, class V, std::size_t N, typename Numeric>
constexpr inline auto operator* (
    Numeric n, rate::rate<D, V, N> const& rt
) noexcept {
    return rate::rate<D, V, N> { rt.value() * n, rt.duration() };
}

}

namespace rate_literals {

constexpr auto operator "" _fps (std::size_t n)  { return rate::fps(n); }
constexpr auto operator "" _bps (std::size_t n)  { return rate::bps(n); }
constexpr auto operator ""  _Hz (std::size_t n)  { return rate::Hz(n); }
constexpr auto operator "" _kHz (std::size_t n)  { return rate::Hz(n); }
constexpr auto operator "" _MHz (std::size_t n)  { return rate::MHz(n); }
constexpr auto operator "" _GHz (std::size_t n)  { return rate::GHz(n); }

}

}

#endif /// KCPPT_RATE_HPP
