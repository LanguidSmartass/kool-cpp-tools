/** @file bank.cpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   16.05.2019
 * 
 * @brief  google tests for ioreg_bank class template
 * 
 */

#include <kcppt/ioreg.hpp>
#include <kcppt/range.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
