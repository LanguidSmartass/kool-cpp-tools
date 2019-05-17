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

if ("${install-path}" STREQUAL "")
    message(FATAL_ERROR "Provide 'install-path' variable!")
endif()

set(
    public-cmake-package-config-path
    ${install-path}/${library-name}
)

set(
    public-header-root-interface-path
    ${public-cmake-package-config-path}/include
)

set(
    headers-root-sources
    ${CMAKE_CURRENT_LIST_DIR}/include
)

set(
    headers-root-install
    ${public-header-root-interface-path}/${library-name}
)

add_library(
    ${library-name}
    INTERFACE
)

target_include_directories(
    ${library-name}
    INTERFACE
    $<BUILD_INTERFACE:${headers-root-sources}>
    $<INSTALL_INTERFACE:${public-header-root-interface-path}>
)

include(include/kcppt/headers.cmake)

set(headers-list-sources ${headers-list-template})
set(headers-list-install ${headers-list-template})

function(list_prepend input_list prefix)
    set(output_list "")
    foreach(item ${${input_list}})
        list(APPEND output_list "${prefix}${item}")
    endforeach()
    set(${input_list} ${output_list} PARENT_SCOPE)
endfunction()

list_prepend(headers-list-sources "${headers-root-sources}/")
list_prepend(headers-list-install "${headers-root-install}/")

set_property(
    TARGET ${library-name}
    PROPERTY INTERFACE_SOURCES ${headers-list-install}
)

install(
    DIRECTORY
    ${headers-root-sources}/ # this trailing slash is crucial, otherwise the 'directory' itself will be copied
    DESTINATION
    ${public-header-root-interface-path}/${library-name} # and this should not have the trailing slash
)

install(
    TARGETS
    ${library-name}
    EXPORT
    ${package-config-file}
    DESTINATION
    ${public-cmake-package-config-path}
)

install(
    EXPORT
    ${package-config-file}
    DESTINATION
    ${public-cmake-package-config-path}
)

#unset(public-header-root-interface-path)
#unset(public-cmake-package-config-path)
#unset(headers-root-sources)
#unset(headers-list-install)
