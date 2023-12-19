cmake_minimum_required(VERSION 3.26)

project(solution)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
endif() 

configure_file(
    "${CMAKE_SOURCE_DIR}/../data.in" 
    "${CMAKE_BINARY_DIR}/Debug/data.in"
    COPYONLY
)

add_executable(${PROJECT_NAME} main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)