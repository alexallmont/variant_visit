cmake_minimum_required(VERSION 3.6)

# Global project settings
project(variant_visit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Fetch external libraries
Include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.10.x
)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.5.4
)

# For Windows, prevent override of parent project's compiler/linker settings (via GoogleTest CMake quickstart guide)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Don't build benchmark tests
set(BENCHMARK_ENABLE_TESTING OFF)

FetchContent_MakeAvailable(
  googletest
  googlebenchmark
)

enable_testing(true)

# Include dependants
add_subdirectory(include)
add_subdirectory(benchmark)
add_subdirectory(tests)
