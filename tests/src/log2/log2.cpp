/** @file log2.cpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   17.05.2019
 * 
 * @brief  
 * 
 */

#include <kcppt/log2.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(log2, next_greater_equal) {
    using kcppt::log2::log2_ge;
    ASSERT_EQ(log2_ge(0), std::numeric_limits<std::intmax_t>::min());
    ASSERT_EQ(log2_ge(1), 0);
    ASSERT_EQ(log2_ge(2), 1);
    ASSERT_EQ(log2_ge(3), 2);
    ASSERT_EQ(log2_ge(5), 3);
    ASSERT_EQ(log2_ge(9), 4);
}

//TEST(log2, next_less_equal) {
//    using kcppt::log2::log2_le;
//    ASSERT_EQ(log2_le(0), std::numeric_limits<std::intmax_t>::min());
//    ASSERT_EQ(log2_le(1), 0);
//    ASSERT_EQ(log2_le(2), 1);
//    ASSERT_EQ(log2_le(3), 2);
//    ASSERT_EQ(log2_le(5), 2);
//    ASSERT_EQ(log2_le(9), 3);
//}
