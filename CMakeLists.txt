# @file CMakeLists.txt
#  
# @author Novoselov Ivan
# @email  jedi.orden@gmail.com
# @date   15.03.2019
# 
# @brief CMake package main file for kool-cpp-tool library
# kcppt is an abbreviation, obviously

cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

set(library-name kcppt)
set(project-name ${library-name})
set(package-config-file ${library-name}-config)

project(
    ${project-name}
    VERSION 0.0.1
    LANGUAGES CXX
)

message("Library name: ${library-name}")

#####################################
# otherwise lots of 'template with C linkage' errors will occur
# see this thread: 
# http://cmake.3232098.n2.nabble.com/target-include-directories-and-system-headers-td7597773.html
set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
#####################################

if (testing)
    set(install-path "A:/garbage")
endif()

add_subdirectory(install)

if (testing)
    include(tests/tests.cmake)
endif()

unset(package-config-file)
unset(project-name)
unset(library-name)
