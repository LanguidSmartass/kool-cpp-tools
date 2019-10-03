/** @file byte.cpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   17.05.2019
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
 * @brief  google tests for byte header
 * 
 */

#include <kcppt/byte.hpp>
#include <kcppt/traits.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace kcppt;

TEST(byte_test, initial_value_zero) {
    using byte::byte;
    auto b = byte {};
    ASSERT_EQ(b, 0);
}

TEST(byte_test, operator_sum_integral) {
    using byte::byte;
    auto i = int {1};
    auto b = byte {3};
    
    auto r0 = b + i;
    auto r1 = 3 + i + b;
    
    ASSERT_EQ(r0, 4);
    ASSERT_EQ(r1, 7);
    
    ASSERT_TRUE(kcppt::traits::is_integral_v<decltype(r0)>);
    ASSERT_TRUE(kcppt::traits::is_integral_v<decltype(r1)>);
}

TEST(byte_test, operator_sum_floating_point) {
    using byte::byte;
    auto f = float {2};
    auto b = byte {3};
    
    auto r2 = b + f;
    auto r3 = 1.0 + f + b;
    
    ASSERT_FLOAT_EQ(r2, 5.0);
    ASSERT_FLOAT_EQ(r3, 6.0);
    
    ASSERT_TRUE(kcppt::traits::is_floating_point_v<decltype(r2)>);
    ASSERT_TRUE(kcppt::traits::is_floating_point_v<decltype(r3)>);
}

TEST(byte_test, operator_sum_assignment_integral) {
    using byte::byte;
    auto i = int {1};
    auto b = byte {3};
    b += i;
    ASSERT_EQ(b, 4);
}

TEST(byte_test, operator_sum_assignment_floating_point) {
    using byte::byte;
    auto f = float {1.0};
    auto b = byte {3};
    b += f;
    ASSERT_EQ(b, 4);
}

TEST(byte_unsigned_test, overflow_integral) {
    using byte::unsigned_byte;
    auto i = int {255};
    auto b = unsigned_byte {3};
    b += i;
    ASSERT_EQ(b, 2);
}

TEST(byte_unsigned_test, underflow_integral) {
    using byte::unsigned_byte;
    auto i = int {8};
    auto b = unsigned_byte {3};
    b -= i;
    ASSERT_EQ(b, 251);
}
