cmake_minimum_required(VERSION 3.6)

# Global project settings
project(variant_visit)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

enable_testing(true)

# Fetch external libraries
Include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.1
)

# For Windows, prevent override of parent project's compiler/linker settings (via GoogleTest CMake quickstart guide)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include dependants
add_subdirectory(include)
add_subdirectory(tests)
