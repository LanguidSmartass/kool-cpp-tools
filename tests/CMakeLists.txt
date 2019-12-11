add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

set(gtests-exec-name kcppt-gtests)

add_executable(
    ${gtests-exec-name}
    src/main.cpp
    src/ioreg/single.cpp
    src/ioreg/bank.cpp
    src/pow2/pow2.cpp
    src/log2/log2.cpp
    src/c_string/c_string.cpp
    src/contiguous_array/contiguous_array.cpp
    src/byte/byte.cpp
    src/allocators/beefy/beefy.cpp
    src/functional/functional.cpp
    src/smart_enum/smart_enum.cpp
    src/rate/rate.cpp
    src/loop_if/loop_if.cpp
    src/img/morph/bin_struct.cpp
    src/img/filt/max_filt.cpp
)

# link the sources of this library to test
include_directories(
    ${gtests-exec-name}
    PRIVATE
    "../install/include"
)

# link google test headers
target_link_libraries(
    ${gtests-exec-name}
    gtest
    gtest_main
)

target_compile_options(
    ${gtests-exec-name}
    PRIVATE
    #-MTd
)

include(toolchain_options.cmake)
