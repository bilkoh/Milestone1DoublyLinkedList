cmake_minimum_required(VERSION 3.25.0)
project(Milestone1 VERSION 0.1.0 LANGUAGES C CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GTest Block Start
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(Milestone1Tests test_main.cc doubly_linked_list.cpp dll_node.cpp)
target_link_libraries(Milestone1Tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(Milestone1Tests)
# GTest Block End

# Main exe 
add_executable(Milestone1 milestone1.cpp doubly_linked_list.cpp generate_output.cpp dll_node.cpp)

# Add a custom target to run tests automatically after the build
add_custom_target(
  run_all_tests
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -V
  DEPENDS Milestone1Tests
)

# Make the custom target run after the build
add_dependencies(Milestone1 run_all_tests)