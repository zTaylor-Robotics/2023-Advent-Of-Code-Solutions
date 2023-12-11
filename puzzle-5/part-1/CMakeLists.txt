cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")
add_definitions(-std=c++2b)

project(puzzle-5-pt-1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug) 
configure_file(
    "${CMAKE_SOURCE_DIR}/../puzzle-5.txt" 
    "${CMAKE_BINARY_DIR}/Debug/puzzle-5.txt"
    COPYONLY
)

add_executable(${PROJECT_NAME} main.cpp)