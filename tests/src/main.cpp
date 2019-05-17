/** @file main.cpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   15.03.2019
 * 
 * @brief  manual testing
 * 
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

auto main (int argc, const char** argv) -> int {
    testing::InitGoogleTest(&argc, const_cast<char**>(argv));
    return RUN_ALL_TESTS();
}
