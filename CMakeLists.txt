cmake_minimum_required(VERSION 3.28)

project(
  spsc_queue
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/main.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES "./src/*.cpp")
add_executable(spsc_queue ${SOURCES})

set (CMAKE_CXX_FLAGS "-std=c++23 ${CMAKE_CXX_FLAGS}")

set_target_properties(spsc_queue PROPERTIES 
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(CONTAINER)
  target_compile_definitions(spsc_queue PRIVATE CONTAINER=${CONTAINER})
else()
  target_compile_definitions(spsc_queue PRIVATE CONTAINER=deque)
endif()

enable_testing()

add_executable(
  spsc_tests
  test/spsc_tests.cpp
  src/spsc_queue.cpp
)

target_include_directories(spsc_tests PRIVATE src)

target_compile_options(spsc_tests PRIVATE --coverage)
target_link_options(spsc_tests PRIVATE --coverage)

target_link_libraries(
  spsc_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(spsc_tests
  PROPERTIES USES_TERMINAL TRUE
)
