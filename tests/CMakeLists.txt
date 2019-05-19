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
    src/byte/byte.cpp
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