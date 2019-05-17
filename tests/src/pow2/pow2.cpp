/** @file pow2.cpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   17.05.2019
 * 
 * @brief  google tests for pow2 functions
 * 
 */

#include <kcppt/pow2.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(pow2, is_pow2) {
    using kcppt::pow2::is_pow2;
    ASSERT_TRUE(is_pow2(0));
    ASSERT_TRUE(is_pow2(1));
    ASSERT_TRUE(is_pow2(2));
    ASSERT_TRUE(is_pow2(512u));
    ASSERT_TRUE(is_pow2(4096));
    ASSERT_TRUE(is_pow2(65536ull));
    ASSERT_TRUE(is_pow2(0x1000000000));
    auto max_pow2 =
        std::uintmax_t(0b1) <<
        (std::numeric_limits<std::uintmax_t>::digits - 1u);
    ASSERT_TRUE(is_pow2(max_pow2));
}

TEST(pow2, is_not_pow2) {
    using kcppt::pow2::is_pow2;
    ASSERT_FALSE(is_pow2(-33));
    ASSERT_FALSE(is_pow2(3));
    ASSERT_FALSE(is_pow2(7));
    ASSERT_FALSE(is_pow2(1337u));
    ASSERT_FALSE(is_pow2(6006135));
    ASSERT_FALSE(is_pow2(0xDEADBEEFu));
    ASSERT_FALSE(is_pow2(std::numeric_limits<std::uintmax_t>::max()));
}

TEST(pow2, next_greater_equal) {
    using kcppt::pow2::pow2_ge;
    ASSERT_EQ(pow2_ge(0), 0);
    ASSERT_EQ(pow2_ge(1), 1);
    ASSERT_EQ(pow2_ge(2), 2);
    ASSERT_EQ(pow2_ge(3), 4);
    ASSERT_EQ(pow2_ge(5), 8);
    ASSERT_EQ(pow2_ge(259), 512);
    ASSERT_EQ(pow2_ge(0xEADBEEF), 0x10000000);
}

TEST(pow2, next_less_equal) {
    using kcppt::pow2::pow2_le;
    ASSERT_EQ(pow2_le(0), 0);
    ASSERT_EQ(pow2_le(1), 1);
    ASSERT_EQ(pow2_le(2), 2);
    ASSERT_EQ(pow2_le(3), 2);
    ASSERT_EQ(pow2_le(5), 4);
    ASSERT_EQ(pow2_le(259), 256);
    ASSERT_EQ(pow2_le(0xEADBEEF), 0x8000000);
}
