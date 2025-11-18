cmake_minimum_required(VERSION 3.10)

project(base_log LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.2.1
)
FetchContent_MakeAvailable(fmt)

set_target_properties(fmt PROPERTIES POSITION_INDEPENDENT_CODE ON)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)
option(BASE_LOG_SHARED "Build base_log as shared lib" ON)

# Try to find Qt Core for Qt-based logging
find_package(Qt6 QUIET COMPONENTS Core)

add_library(base_log
    "${CMAKE_CURRENT_SOURCE_DIR}/include/base_log.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/base_log.cpp"
)

if(BASE_LOG_SHARED)
    set_target_properties(base_log PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        BUILD_SHARED_LIBS ON
    )

endif()

target_compile_definitions(base_log
    PUBLIC
        PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}/"
)

# Check if existed LOG_TAG macro is defined
# If not , got the ROOT project name as LOG_TAG
if(NOT DEFINED LOG_TAG)
    get_filename_component(ROOT_PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)
    target_compile_definitions(base_log
        PUBLIC
            LOG_TAG="${ROOT_PROJECT_NAME}"
    )
endif()

target_link_libraries(base_log
    PUBLIC
        fmt::fmt
)

# If Qt6 Core is found, enable Qt logging
if(Qt6_FOUND AND TARGET Qt6::Core)
    message(STATUS "base_log: Qt6 Core found, enabling Qt logging support")
    target_compile_definitions(base_log
        PUBLIC
            BASE_LOG_USE_QT
    )
    target_link_libraries(base_log
        PUBLIC
            Qt6::Core
    )
else()
    message(STATUS "base_log: Qt6 Core not found, using standard iostream logging")
endif()

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
