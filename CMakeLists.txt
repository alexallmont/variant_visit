cmake_minimum_required(VERSION 3.6)

# Global project settings
project(variant_visit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Required for Google Benchmark
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(BENCHMARK_ENABLE_LTO)
set(HAVE_STD_REGEX 0)
set(HAVE_GNU_POSIX_REGEX 0)
set(HAVE_POSIX_REGEX 0)

if(MSVC)
  set(CMAKE_CXX_FLAGS "/W4")
  set(CMAKE_CXX_FLAGS_DEBUG "/Zi")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else()
  set(CMAKE_CXX_FLAGS "-Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

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
set(gbenchmark_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(
  googletest
  googlebenchmark
)

enable_testing(true)

# Include dependants
add_subdirectory(include)
add_subdirectory(benchmark)
add_subdirectory(tests)
