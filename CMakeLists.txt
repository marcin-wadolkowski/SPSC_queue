cmake_minimum_required(VERSION 3.28)

project(
  spsc_queue
  VERSION 1.0
  LANGUAGES CXX)

file(GLOB SOURCES "./src/*.cpp")
add_executable(spsc_queue ${SOURCES})

set_target_properties(spsc_queue PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)