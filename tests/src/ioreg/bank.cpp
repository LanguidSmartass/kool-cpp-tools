/** @file bank.cpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   16.05.2019
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
 * @brief  google tests for ioreg_bank class template
 * 
 */

#include <kcppt/ioreg.hpp>
#include <kcppt/range.hpp>
#include <kcppt/debug.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

constexpr static auto _bank_size = 5;
constexpr static std::uint32_t _default_values [_bank_size] {
    42, 1337, 0xFACE0FF, 0xB00B135, 0xDEFEC8ED
};
/// Represents a bank of registers of some device with memory-mapped IO
static std::uint32_t _bank_raw [_bank_size];

//using access_t = kcppt::ioreg::_implementation::accessor<_bank_raw>;
//constexpr static auto dbg = kcppt::debug::display_type_inside_incomplete_type_error(access_t{});
//static_assert(std::is_same_v<void, access_t>);
//using _obj_type = kcppt::ioreg::rb_ptr<_bank_raw, _bank_size>;
//using _raw_type = typename _obj_type::type;

class ioreg_bank_test : public ::testing::Test {
protected:
    constexpr static auto _bank_size = 5;
    constexpr static std::uint32_t _default_values [_bank_size] {
        42, 1337, 0xFACE0FF, 0xB00B135, 0xDEFEC8ED
    };
    /**
     * @brief raw memory under test
     */
    static std::uint32_t _bank_raw [_bank_size];

    /**
     * @brief type alias
     */
    using _obj_type = kcppt::ioreg::rb_ptr<_bank_raw, _bank_size>;
    using _raw_type = _obj_type::type;
    //constexpr static auto c  =  kcppt::debug::display_type_inside_incomplete_type_error<std::decay_t<decltype(_bank_raw)>>({});
//    constexpr static auto cc  =  kcppt::debug::display_type_inside_incomplete_type_error<typename _obj_type::type>({});
    /**
     * @brief class template instance under test
     */
    _obj_type _bank_obj;

    ioreg_bank_test () = default;

    virtual ~ioreg_bank_test () noexcept = default;

    /**
     * @brief setup the default value
     */
    auto SetUp () -> void override {
        for (auto i : kcppt::range::range(_bank_size)) {
            _bank_raw[i] = _default_values[i];
        }
    }

    auto TearDown () -> void override {}

};

std::uint32_t ioreg_bank_test::_bank_raw[] {};

TEST_F(ioreg_bank_test, setup_values_correct) {
    for (auto i : kcppt::range::range(_bank_size)) {
        ASSERT_EQ(_default_values[i], _bank_raw[i]);
    }
}

TEST_F(ioreg_bank_test, size) {
    ASSERT_EQ(_bank_size, _bank_obj.size());
}

TEST_F(ioreg_bank_test, operator_subscript) {
    for (auto i : kcppt::range::range(_bank_obj.size())) {
        ASSERT_EQ(_bank_raw[i], _bank_obj[i]);
    }
}

