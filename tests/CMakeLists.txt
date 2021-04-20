add_executable(tests
  main.cpp
  test_visit.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2 variant_visit)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)
catch_discover_tests(tests)
