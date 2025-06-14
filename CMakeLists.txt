cmake_minimum_required(VERSION 3.10)

project(base_log LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.2.1
)
FetchContent_MakeAvailable(fmt)


add_library(base_log
    "${CMAKE_CURRENT_SOURCE_DIR}/include/base_log.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/base_log.cpp"
)

target_link_libraries(base_log
    PUBLIC
        fmt::fmt
)

target_include_directories(base_log PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add test target with option
option(ENABLE_TESTS "Enable tests" OFF)
if(ENABLE_TESTS)
    find_package(GTest REQUIRED)
    enable_testing()  # Enable CTest

    # Add test executable
    add_executable(test_base_log tests/test.cpp)

    # Link the test executable with the base_log library and GTest
    target_link_libraries(test_base_log PRIVATE GTest::gtest_main base_log)

    # Register the test with CTest
    add_test(NAME TestBaseLog COMMAND test_base_log)
endif()
