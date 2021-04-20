cmake_minimum_required(VERSION 3.6)

# Global project settings
project(variant_visit)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

enable_testing(true)

# Get Catch2 for unit testing
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

# Include dependants
add_subdirectory(include)
add_subdirectory(tests)
