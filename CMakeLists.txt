# @file CMakeLists.txt
#  
# @author Novoselov Ivan
# @email  jedi.orden@gmail.com
# @date   15.03.2019
#
# MIT License
#
# Copyright (c) 2019 Ivan Novoselov
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
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
