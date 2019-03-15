/** @file endian.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   03.03.2019
 * 
 * @brief  
 * 
 */

#ifndef KCPPT_ENDIAN_HPP
#define KCPPT_ENDIAN_HPP

#include <cinttypes>

namespace kcppt {

namespace endian {

union endian {
private:
    std::uint16_t _word;
    std::uint8_t _bytes[sizeof(_word)];
public:
    constexpr endian () noexcept : _word(0x0201u) {}
    
    [[nodiscard]]
    constexpr auto little () const noexcept -> bool {
        return _bytes[0u] == 0x01u;
    }
    
    [[nodiscard]]
    constexpr auto big () const noexcept -> bool {
        return _bytes[0u] == 0x02u;
    }
};

}

}

#endif /// KCPPT_ENDIAN_HPP
