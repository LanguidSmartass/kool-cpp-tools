/** @file single.cpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   16.05.2019
 * 
 * @brief  google tests for ioreg_single class template
 * 
 */

#include <kcppt/ioreg.hpp>
#include <utility>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class ioreg_single_test : public ::testing::Test {
protected:
    /**
     * @brief raw memory under test
     */
    static /*const auto */ std::uint32_t _reg_raw;
    /**
     * @brief type alias
     */
    using reg_obj_type = kcppt::ioreg::rs_ptr<&_reg_raw>;
    using reg_raw_type = reg_obj_type::type;
    /**
     * @brief class template under test
     */
    reg_obj_type _reg_obj;
    
    ioreg_single_test () = default;
    
    virtual ~ioreg_single_test () noexcept = default;
    
    constexpr static decltype(_reg_raw) _default_value = 0xDEFEC8ED;
    
    /**
     * @brief setup the default value
     */
    auto SetUp () -> void override {
        _reg_obj = _default_value;
    }
    
    auto TearDown () -> void override {}
    
};

std::uint32_t ioreg_single_test::_reg_raw {};

TEST_F(ioreg_single_test, setup_value_correct) {
    ASSERT_EQ(_reg_obj, _default_value);
}

TEST_F(ioreg_single_test, operator_type_conversion) {
    ASSERT_TRUE((std::is_same_v<reg_obj_type::type, decltype(_reg_raw)>));
}

TEST_F(ioreg_single_test, operator_bit_and) {
    constexpr reg_raw_type mask_and = 0x11111111;
    constexpr reg_raw_type expected_result = _default_value & mask_and;
    auto result = _reg_obj & mask_and;
    ASSERT_EQ(result, expected_result);
}

TEST_F(ioreg_single_test, operator_bit_or) {
    constexpr reg_raw_type mask_or = 0x20000300;
    constexpr reg_raw_type expected_result = _default_value | mask_or;
    auto result = _reg_obj | mask_or;
    ASSERT_EQ(result, expected_result);
}

TEST_F(ioreg_single_test, operator_bit_xor) {
    constexpr reg_raw_type mask_xor = 0xDEFECBED;
    constexpr reg_raw_type expected_result = _default_value ^ mask_xor;
    auto result = _reg_obj ^ mask_xor;
    ASSERT_EQ(result, expected_result);
}

TEST_F(ioreg_single_test, operator_bit_not) {
    constexpr reg_raw_type expected_result = ~_default_value;
    auto result = ~_reg_obj;
    ASSERT_EQ(result, expected_result);
}

TEST_F(ioreg_single_test, operator_bit_shift_left) {
    constexpr auto bp = 19;
    constexpr auto expected_result = _default_value << bp;
    auto result = _reg_obj << bp;
    ASSERT_EQ(result, expected_result);
}

TEST_F(ioreg_single_test, operator_bit_shift_right) {
    constexpr auto bp = 7;
    constexpr auto expected_result = _default_value >> bp;
    auto result = _reg_obj >> bp;
    ASSERT_EQ(result, expected_result);
}

TEST_F(ioreg_single_test, operator_assignment) {
    constexpr reg_raw_type new_value = 0xFACE0FF;
    _reg_obj = new_value;
    ASSERT_EQ(_reg_obj, _reg_raw);
    ASSERT_EQ(_reg_obj, new_value);
    ASSERT_EQ(_reg_raw, new_value);
}

TEST_F(ioreg_single_test, operator_bit_and_assign) {
    constexpr reg_raw_type mask_and = 0x11111111;
    constexpr reg_raw_type expected_result = _default_value & mask_and;
    _reg_obj &= mask_and;
    ASSERT_EQ(_reg_obj, _reg_raw);
    ASSERT_EQ(_reg_obj, expected_result);
    ASSERT_EQ(_reg_raw, expected_result);
}

TEST_F(ioreg_single_test, operator_bit_or_assign) {
    constexpr reg_raw_type mask_or = 0x20000300;
    constexpr reg_raw_type expected_result = _default_value | mask_or;
    _reg_obj |= mask_or;
    ASSERT_EQ(_reg_obj, _reg_raw);
    ASSERT_EQ(_reg_obj, expected_result);
    ASSERT_EQ(_reg_raw, expected_result);
}

TEST_F(ioreg_single_test, operator_bit_xor_assign) {
    constexpr reg_raw_type mask_xor = 0xDEFECBED;
    constexpr reg_raw_type expected_result = _default_value ^ mask_xor;
    _reg_obj ^= mask_xor;
    ASSERT_EQ(_reg_obj, _reg_raw);
    ASSERT_EQ(_reg_obj, expected_result);
    ASSERT_EQ(_reg_raw, expected_result);
}

TEST_F(ioreg_single_test, operator_bit_shift_left_assign) {
    constexpr auto bp = 19;
    constexpr auto expected_result = _default_value << bp;
    _reg_obj <<= bp;
    ASSERT_EQ(_reg_obj, _reg_raw);
    ASSERT_EQ(_reg_obj, expected_result);
    ASSERT_EQ(_reg_raw, expected_result);
}

TEST_F(ioreg_single_test, operator_bit_shift_right_assign) {
    constexpr auto bp = 7;
    constexpr auto expected_result = _default_value >> bp;
    _reg_obj >>= bp;
    ASSERT_EQ(_reg_obj, _reg_raw);
    ASSERT_EQ(_reg_obj, expected_result);
    ASSERT_EQ(_reg_raw, expected_result);
}
