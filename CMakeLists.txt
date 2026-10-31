cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW)
project(lana_matrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# force GoogleTest to use the shared MSVC runtime to avoid runtime library mismatch
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(matrix_test
    tests/matrix_test.cpp
)

target_include_directories(matrix_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core
)

target_link_libraries(matrix_test PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix_test)