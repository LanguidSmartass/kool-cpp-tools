/** @file c_string.cpp
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
 * @brief  google tests for c_string header
 * 
 */

#include <kcppt/c_string.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace kcppt;

/******************************************************************************/
/// STRCMP RUNTIME
/******************************************************************************/

TEST(c_string_test, strcmp_rtime_empty_lhs_rhs) {
    using c_string::strcmp;
    auto str0 = "";
    auto str1 = "";
    auto result = strcmp(str0, str1);
    ASSERT_EQ(result, 0);
}

TEST(c_string_test, strcmp_rtime_empty_lhs) {
    using c_string::strcmp;
    auto str0 = "";
    auto str1 = "1";
    auto result = strcmp(str0, str1);
    ASSERT_TRUE(result < 0);
}

TEST(c_string_test, strcmp_rtime_empty_rhs) {
    using c_string::strcmp;
    auto str0 = "1";
    auto str1 = "";
    auto result = strcmp(str0, str1);
    ASSERT_TRUE(result > 0);
}

TEST(c_string_test, strcmp_rtime_eq) {
    using c_string::strcmp;
    auto str0 = "I am a basic ASCII C-string";
    auto str1 = "I am a basic ASCII C-string";
    auto result = strcmp(str0, str1);
    ASSERT_EQ(result, 0);
}

TEST(c_string_test, strcmp_rtime_gt) {
    using c_string::strcmp;
    auto str0 = "I am a basic ASCII C-string";
    auto str1 = "I am A";
    auto result = strcmp(str0, str1);
    ASSERT_TRUE(result > 0);
}

TEST(c_string_test, strcmp_rtime_less) {
    using c_string::strcmp;
    auto str0 = "I am a basic ASCII C-string";
    auto str1 = "I am z";
    auto result = strcmp(str0, str1);
    ASSERT_TRUE(result < 0);
}

/******************************************************************************/
/// STRCMP COMPILETIME
/******************************************************************************/

TEST(c_string_test, strcmp_ctime_empty_lhs_rhs) {
    using c_string::strcmp;
    constexpr auto str0 = "";
    constexpr auto str1 = "";
    constexpr auto result = strcmp(str0, str1);
    ASSERT_EQ(result, 0);
}

TEST(c_string_test, strcmp_ctime_empty_lhs) {
    using c_string::strcmp;
    constexpr auto str0 = "";
    constexpr auto str1 = "1";
    constexpr auto result = strcmp(str0, str1);
    ASSERT_TRUE(result < 0);
}

TEST(c_string_test, strcmp_ctime_empty_rhs) {
    using c_string::strcmp;
    constexpr auto str0 = "1";
    constexpr auto str1 = "";
    constexpr auto result = strcmp(str0, str1);
    ASSERT_TRUE(result > 0);
}

TEST(c_string_test, strcmp_ctime_eq) {
    using c_string::strcmp;
    constexpr auto str0 = "I am a basic ASCII C-string";
    constexpr auto str1 = "I am a basic ASCII C-string";
    constexpr auto result = strcmp(str0, str1);
    ASSERT_EQ(result, 0);
}

TEST(c_string_test, strcmp_ctime_gt) {
    using c_string::strcmp;
    constexpr auto str0 = "I am a basic ASCII C-string";
    constexpr auto str1 = "I am A";
    constexpr auto result = strcmp(str0, str1);
    ASSERT_TRUE(result > 0);
}

TEST(c_string_test, strcmp_ctime_less) {
    using c_string::strcmp;
    constexpr auto str0 = "I am a basic ASCII C-string";
    constexpr auto str1 = "I am z";
    constexpr auto result = strcmp(str0, str1);
    ASSERT_TRUE(result < 0);
}

/******************************************************************************/
/// STRLEN RUNTIME
/******************************************************************************/

TEST(c_string_test, strnlen_rtime_empty) {
    using c_string::strlen;
    auto str = "";
    auto result = strlen(str);
    ASSERT_EQ(result, 0);
}

TEST(c_string_test, strnlen_rtime_one) {
    using c_string::strlen;
    auto str = "0";
    auto result = strlen(str);
    ASSERT_EQ(result, 1);
}

TEST(c_string_test, strnlen_rtime_ten) {
    using c_string::strlen;
    auto str = "0123456789";
    auto result = strlen(str);
    ASSERT_EQ(result, 10);
}

/******************************************************************************/
/// STRLEN COMPILETIME
/******************************************************************************/

TEST(c_string_test, strnlen_ctime_empty) {
    using c_string::strlen;
    constexpr auto str = "";
    constexpr auto result = strlen(str);
    ASSERT_EQ(result, 0);
}

TEST(c_string_test, strnlen_ctime_one) {
    using c_string::strlen;
    constexpr auto str = "0";
    constexpr auto result = strlen(str);
    ASSERT_EQ(result, 1);
}

TEST(c_string_test, strnlen_ctime_ten) {
    using c_string::strlen;
    constexpr auto str = "0123456789";
    constexpr auto result = strlen(str);
    ASSERT_EQ(result, 10);
}

/******************************************************************************/
/// IS_C_STRING RUNLETIME
/******************************************************************************/

TEST(c_string_test, is_c_string_rtime_nullptr) {
    using c_string::is_c_string;
    auto str = nullptr;
    auto result = is_c_string(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_empty) {
    using c_string::is_c_string;
    auto str = "";
    auto result = is_c_string(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_default) {
    using c_string::is_c_string;
    auto str = "I am a basic ASCII C-string";
    auto result = is_c_string(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_ascii_true) {
    using c_string::is_c_string;
    using c_string::is_ascii;
    auto str = "\ncCF 123!!\t";
    auto result = is_c_string<is_ascii>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_ascii_false) {
    using c_string::is_c_string;
    using c_string::is_ascii;
    const char str[] = {char(0x80), char(0x91), char(0xFF), '\0'};
    auto result = is_c_string<is_ascii>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_lf_true) {
    using c_string::is_c_string;
    using c_string::is_lf;
    auto str = "\n\n\n";
    auto result = is_c_string<is_lf>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_lf_false) {
    using c_string::is_c_string;
    using c_string::is_lf;
    auto str = "\n\n33";
    auto result = is_c_string<is_lf>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_cr_true) {
    using c_string::is_c_string;
    using c_string::is_cr;
    auto str = "\r\r\r";
    auto result = is_c_string<is_cr>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_cr_false) {
    using c_string::is_c_string;
    using c_string::is_cr;
    auto str = "\r\r11";
    auto result = is_c_string<is_cr>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_tab_true) {
    using c_string::is_c_string;
    using c_string::is_tab;
    auto str = "\t\t\t";
    auto result = is_c_string<is_tab>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_tab_false) {
    using c_string::is_c_string;
    using c_string::is_tab;
    auto str = "\t\t22";
    auto result = is_c_string<is_tab>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_space_true) {
    using c_string::is_c_string;
    using c_string::is_space;
    auto str = "   ";
    auto result = is_c_string<is_space>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_space_false) {
    using c_string::is_c_string;
    using c_string::is_space;
    auto str = " ! ";
    auto result = is_c_string<is_space>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_upper_true) {
    using c_string::is_c_string;
    using c_string::is_upper;
    auto str = "AA";
    auto result = is_c_string<is_upper>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_upper_false) {
    using c_string::is_c_string;
    using c_string::is_upper;
    auto str = "Aa";
    auto result = is_c_string<is_upper>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_lower_true) {
    using c_string::is_c_string;
    using c_string::is_lower;
    auto str = "aa";
    auto result = is_c_string<is_lower>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_lower_false) {
    using c_string::is_c_string;
    using c_string::is_lower;
    auto str = "aA";
    auto result = is_c_string<is_lower>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_nonprint_true) {
    using c_string::is_c_string;
    using c_string::is_nonprint;
    auto str = "\t\n\r";
    auto result = is_c_string<is_nonprint>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_nonprint_false) {
    using c_string::is_c_string;
    using c_string::is_nonprint;
    auto str = "\t\r22";
    auto result = is_c_string<is_nonprint>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_bin_true) {
    using c_string::is_c_string;
    using c_string::is_bin;
    auto str = "01101010";
    auto result = is_c_string<is_bin>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_bin_false) {
    using c_string::is_c_string;
    using c_string::is_bin;
    auto str = "021101010";
    auto result = is_c_string<is_bin>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_oct_true) {
    using c_string::is_c_string;
    using c_string::is_oct;
    auto str = "0167435";
    auto result = is_c_string<is_oct>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_oct_false) {
    using c_string::is_c_string;
    using c_string::is_oct;
    auto str = "016743588";
    auto result = is_c_string<is_oct>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_dec_true) {
    using c_string::is_c_string;
    using c_string::is_dec;
    auto str = "9462871053";
    auto result = is_c_string<is_dec>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_dec_false) {
    using c_string::is_c_string;
    using c_string::is_dec;
    auto str = "946F2871053E";
    auto result = is_c_string<is_dec>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_hex_true) {
    using c_string::is_c_string;
    using c_string::is_hex;
    auto str = "1FaCe0Ff";
    auto result = is_c_string<is_hex>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_hex_false) {
    using c_string::is_c_string;
    using c_string::is_hex;
    auto str = "1Cage0Ff";
    auto result = is_c_string<is_hex>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_hex_low_true) {
    using c_string::is_c_string;
    using c_string::is_hex_low;
    auto str = "1face0ff";
    auto result = is_c_string<is_hex_low>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_hex_low_false) {
    using c_string::is_c_string;
    using c_string::is_hex_low;
    auto str = "1cage0ff";
    auto result = is_c_string<is_hex_low>(str);
    ASSERT_FALSE(result);
}

TEST(c_string_test, is_c_string_rtime_only_hex_up_true) {
    using c_string::is_c_string;
    using c_string::is_hex_up;
    auto str = "1FACE0FF";
    auto result = is_c_string<is_hex_up>(str);
    ASSERT_TRUE(result);
}

TEST(c_string_test, is_c_string_rtime_only_hex_up_false) {
    using c_string::is_c_string;
    using c_string::is_hex_up;
    auto str = "1CAGE0FF";
    auto result = is_c_string<is_hex_up>(str);
    ASSERT_FALSE(result);
}

/******************************************************************************/
/// IS_C_STRING COMPILETIME
/******************************************************************************/

TEST(c_string_test, is_c_string_ctime_default) {
    using c_string::is_c_string;
    constexpr auto str = "I am a basic ASCII C-string";
    constexpr auto result = is_c_string(str);
    ASSERT_TRUE(result);
}
