/** @file smart_enum.cpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   24.09.2019
 * 
 * @brief  
 * 
 */

#include <kcppt/smart_enum.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
/*
TEST(smart_enum_named, ctor_dtor) {
    using namespace kcppt::smart_enum;
    
    auto value0 = 42;
    auto value1 = 42.0;
    
    auto name0 = "char C-string";
    auto name1 = L"wide char C-string";
    
    auto e_str_char = smart_enum_named(value0, name0);
    auto e_str_wchar = smart_enum_named(value1, name1);
    
    auto value0_get = e_str_char.value();
    auto value1_get = e_str_wchar.value();
    
    auto name0_get = e_str_char.name();
    auto name1_get = e_str_wchar.name();
    
    ASSERT_EQ(value0_get, value0);
    ASSERT_EQ(name0_get, name0);
    ASSERT_EQ(value1_get, value1);
    ASSERT_EQ(name1_get, name1);
}
*/
