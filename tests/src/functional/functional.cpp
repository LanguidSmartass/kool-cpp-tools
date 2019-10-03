/** @file functional.cpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   24.09.2019
 * 
 * @brief  
 * 
 */

#include <kcppt/functional.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST (merge_lambdas, no_captures_different_arguments) {
    using namespace kcppt::functional;
    
    auto l0 = [](int){ return 1; };
    auto l1 = [](double){ return 2; };
    auto l2 = [](char){ return 3; };

    auto super_l = merge {l0, l1, l2};
    
    ASSERT_EQ(super_l(42), 1);
    ASSERT_EQ(super_l(42.0), 2);
    ASSERT_EQ(super_l('c'), 3);
}
