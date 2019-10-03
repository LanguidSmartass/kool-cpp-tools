/** @file serial.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   02.10.2019
 * 
 * @brief  
 * 
 */

#ifndef KCPPT_SERIAL_HPP
#define KCPPT_SERIAL_HPP

#include <string_view>
#include <cinttypes>

namespace kcppt::serial {

namespace bitwidth {
constexpr static auto dtb = 4u;
constexpr static auto prt = 2u;
constexpr static auto stb = 1u;
}

namespace bitpos {
constexpr static auto dtb = 4u;
constexpr static auto prt = 2u;
constexpr static auto stb = 1u;
}

namespace bitmask {
constexpr static auto dtb = 0b1111u << bitpos::dtb;
constexpr static auto prt = 0b11u << bitpos::prt;
constexpr static auto stb = 0b1u << bitpos::stb;
}

using frame_types_base = std::uint_fast8_t;

/**
 * @brief number of data bits, 4 and 9 are rarely spotted but still may be used
 */
enum class dtb : frame_types_base {
    four  = 4u << bitpos::dtb, // 0b0100 << 4
    five  = 5u << bitpos::dtb, // 0b0101 << 4
    six   = 6u << bitpos::dtb, // 0b0110 << 4
    seven = 7u << bitpos::dtb, // 0b0111 << 4
    eight = 8u << bitpos::dtb, // 0b1000 << 4
    nine  = 9u << bitpos::dtb, // 0b1001 << 4
};
/**
 * @brief parity bit
 */
enum class prt : frame_types_base {
    off  = 0u  << bitpos::prt, // 0b0000 << 2
    odd  = 1u  << bitpos::prt, // 0b0100 << 2
    even = 2u << bitpos::prt, // 0b1000 << 2
};
/**
 * @brief number of stop bits
 */
enum class stb : frame_types_base {
    one = 0u << bitpos::stb, // 0b0 << 1
    two = 1u << bitpos::stb, // 0b1 << 1
};

/**
 * @brief squashed frame settings
 */
class alignas(frame_types_base) frm : {
private:
    frame_types_base _m_impl;
    
    constexpr auto _ctor(dtb d, prt p, stb s) noexcept {
        using ftb = frame_types_base;
        return ftb {
            (static_cast<ftb>(d) << bitpos::dtb) |
            (static_cast<ftb>(p) << bitpos::prt) |
            (static_cast<ftb>(p) << bitpos::stb)
        };
    }
    
public:
    explicit constexpr frm (
        dtb d = dtb::eight, prt p = prt::off, stb s = stb::one
    ) noexcept : _m_impl(_ctor(d, p, s)) {}
    
    constexpr data_bits () const noexcept -> dtb {
        return _m_impl & (~bitmask::dtb);
    }
    
    constexpr parity () const noexcept -> prt {
        return _m_impl & (~bitmask::prt);
    }
    
    constexpr stop_bits () const noexcept -> stb {
        return _m_impl & (~bitmask::stb);
    }
};

/**
 * @brief basic serial interface, requires actual implementation class
 * @tparam _Impl -- implementation class
 *
 * @desc "_Impl" class requirements:
 *
 */
template <class _Impl>
class serial {
private:
    // maybe for each function, or just use some expression that looks like
    // "is_noexcept_v<_Impl::func>"
    constexpr static auto _sm_is_noexcept = _Impl::sm_is_noexcept;
    // is that even required?
    constexpr static auto _sm_is_threadsafe = _Impl::sm_is_threadsafe;
    
public:
    // usually std::uint8_t, but can be std::uint16_t if a frame has 9 data bits
    using data_type = typename _Impl::data_type;
    
public:
    serial () noexcept( ) : _m_impl{} {}
    
    /**
     * @brief Allow CTAD from rvalues
     */
    explicit serial (_Impl&& i) noexcept( ) :
    _m_impl{std::move(i)} {}
    
    /**
     * @brief Prevent initializing from copies of _Impl
     */
    serial (const _Impl& i) = delete;
    
    // Id can be integral_type, or a const string type
    template <typename Id, typename = std::enable_if_t<std::is_integral_v<Id> || std::is_string_type_t<Id>>>
    serial (Id&& id, dtb d, prt p, stb s) noexcept( ) :
    _m_impl{std::forward<Id>(id), d, p, s}
    {}
    
    template <typename Id, typename = std::enable_if_t<std::is_integral_v<Id> || std::is_string_type_t<Id>>>
    serial (Id&& id, frm f) noexcept( ) :
        _m_impl{std::forward<Id>(id), f}
    {}
    
    /**
     * @brief cannot be copied
     */
    serial (const serial&) = delete;
    
    serial& operator=(const serial&) = delete;
    
    /**
     * @brief can be moved
     */
    serial (serial&& other) : _m_impl{other._m_impl} {
        other.deinit_on_move();
    }
    
    serial& operator=(serial&& other) {
        _m_impl = other._m_impl;
        other.deinit_on_move();
        return *this;
    }

    virtual ~serial() noexcept { close(); }
    
public:
    [[nodiscard]] auto is_open () noexcept( ) -> bool {
        return _m_impl.is_open();
    }
    
    template <typename Id, typename...Rest>
    auto open (Id&& id, Rest&&...rest) noexcept( ) {
        return _m_impl.open(std::forward<Id>(id), std::forward<Rest>(rest)...);
    }
    
    auto close () noexcept( ) {
        return _m_impl.close();
    }
    
public:
    auto baud (std::size_t b) noexcept( ) {}
    
    [[nodiscard]] auto baud () noexcept( ) -> std::size_t {}
    
    auto data_bits (dtb data_bits) noexcept( ) {}
    
    [[nodiscard]] auto data_bits () noexcept( ) -> dtb {}
    
    auto parity (prt parity) noexcept( ) {}
    
    [[nodiscard]] auto parity () noexcept( ) -> prt {}
    
    auto stop_bits (stb stop_bits) noexcept( ) {}
    
    [[nodiscard]] auto stop_bits () noexcept( ) -> stb {}
    
    auto frame_settings (frm frame) noexcept( ) {}
    
    [[nodiscard]] auto frame_settings () noexcept( ) -> frm {}
    
public: // generic read/write functions
    [[nodiscard]] auto read () noexcept( ) -> data_type {}
    
    auto read (data_type* dst, std::size_t n) noexcept( ) -> std::size_t {}
    
    template <typename OutputIt>
    auto read (OutputIt start, OutputIt end) noexcept( ) -> typename std::iterator_traits<OutputIt>::difference_type {}
    
    template <template <class D> class Container>
    auto read (Container<data_type>& c, std::size_t n) noexcept( ) -> typename Container<data_type>::size_type {}
    
    auto write (data_type d) noexcept( ) {}
    
    auto write (const data_type* src, std::size_t n) noexcept( ) -> std::size_t {}
    
    template <typename InputIt>
    auto write (InputIt start, InputIt end) noexcept( ) -> typename std::iterator_traits<InputIt>::difference_type {}
    
    template <template <class D> class Container>
    auto write (const Container<data_type>& c, std::size_t n) noexcept( ) -> typename Container<data_type>::size_type {}
    
public: // in case you have an underlying buffer
    [[nodiscard]] auto size_read () noexcept( ) -> std::size_t {}
    
    [[nodiscard]] auto size_write () noexcept( ) -> std::size_t {}
    
public: // in case you have interrupt service routines
    auto tx_start () noexcept( ) {}
    
    auto tx_stop () noexcept( ) {}
    
    auto rx_start () noexcept( ) {}
    
    auto rx_stop () noexcept( ) {}

private:
    // Your interface actually may not even have a size, hence the attribute
    [[no_unique_address]] _Impl _m_impl;
    
};

}

#endif /// KCPPT_SERIAL_HPP
