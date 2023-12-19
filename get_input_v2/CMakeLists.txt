cmake_minimum_required(VERSION 3.26)

project(get_input)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
endif() 

add_definitions(-DCURL_STATICLIB)

find_package(CURL REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} "${CURL_LIBRARY}/libcurl.dll.a")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)