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
    ${CMAKE_CURRENT_LIST_DIR}/headers
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
    $<BUILD_INTERFACE:${headers-root-sources}> # for 'building', even thought there is nothing to build
    $<INSTALL_INTERFACE:${public-header-root-interface-path}>
)

include(files-list.cmake)
string(REPLACE "PREFIX_DIR" "${headers-root-sources}" headers-list-sources "${headers-list-template}")
string(REPLACE "PREFIX_DIR" "${headers-root-install}" headers-list-install "${headers-list-template}")
# message("headers-list-sources:  ${headers-list-sources}")
# message("headers-list-install:  ${headers-list-install}")

set_property(
    TARGET ${library-name}
    PROPERTY INTERFACE_SOURCES ${headers-list-install}
)

target_link_libraries(
    ${library-name}
    INTERFACE
    extra-templates
    ipcore
    vend-spec-tables
#    xil-bsp
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

unset(public-header-root-interface-path)
unset(public-cmake-package-config-path)
unset(headers-list)
unset(headers-root)
