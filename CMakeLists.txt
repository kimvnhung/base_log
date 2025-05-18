cmake_minimum_required(VERSION 3.10)

project(base_log LANGUAGES CXX)

find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)
find_package(fmt REQUIRED)

add_library(base_log
    "${CMAKE_CURRENT_SOURCE_DIR}/include/base_log.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/base_log.cpp"
)

target_link_libraries(base_log
    PRIVATE
        spdlog::spdlog
        fmt::fmt
)

target_include_directories(base_log PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add test target with option
option(ENABLE_TESTS "Enable tests" ON)
if(ENABLE_TESTS)
    enable_testing()  # Enable CTest

    # Add test executable
    add_executable(test_base_log tests/test.cpp)

    # Link the test executable with the base_log library and GTest
    target_link_libraries(test_base_log PRIVATE GTest::gtest_main base_log fmt::fmt)

    # Register the test with CTest
    add_test(NAME TestBaseLog COMMAND test_base_log)
endif()
