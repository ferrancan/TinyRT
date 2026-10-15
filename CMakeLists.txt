cmake_minimum_required(VERSION 3.25)
project(tinyrt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings only for our code, not for third-party code
add_library(tinyrt_warnings INTERFACE)
target_compile_options(tinyrt_warnings INTERFACE
  -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wnon-virtual-dtor -Werror)

# Sanitizers chosen by preset: "address,undefined" or "thread"
set(TINYRT_SANITIZER "" CACHE STRING "Sanitizers to enable")
if(TINYRT_SANITIZER)
  add_compile_options(-fsanitize=${TINYRT_SANITIZER} -fno-omit-frame-pointer -g)
  add_link_options(-fsanitize=${TINYRT_SANITIZER})
endif()

# Dependencies (bump the tags to the latest releases)
include(FetchContent)
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG v1.15.2 SYSTEM)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_Declare(benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git GIT_TAG v1.9.1 SYSTEM)
FetchContent_MakeAvailable(googletest benchmark)

# Library
add_library(tinyrt src/tinyrt.cpp)
target_include_directories(tinyrt PUBLIC include)
target_link_libraries(tinyrt PRIVATE tinyrt_warnings)

# Tests
enable_testing()
add_executable(tinyrt_tests tests/test_buffer.cpp)
target_link_libraries(tinyrt_tests PRIVATE tinyrt tinyrt_warnings GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tinyrt_tests)

# Benchmarks
add_executable(tinyrt_bench bench/bench_alloc.cpp)
target_link_libraries(tinyrt_bench PRIVATE tinyrt benchmark::benchmark_main)