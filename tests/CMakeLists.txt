add_executable(tests
  test_visit.cpp
)

target_link_libraries(tests
  PRIVATE
    variant_visit
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)