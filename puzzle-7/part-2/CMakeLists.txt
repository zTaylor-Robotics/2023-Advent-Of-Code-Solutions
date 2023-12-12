cmake_minimum_required(VERSION 3.26)

project(puzzle-6-pt-2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug) 

configure_file(
    "${CMAKE_SOURCE_DIR}/../puzzle-6.txt" 
    "${CMAKE_BINARY_DIR}/Debug/puzzle-6.txt"
    COPYONLY
)

add_executable(${PROJECT_NAME} main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)