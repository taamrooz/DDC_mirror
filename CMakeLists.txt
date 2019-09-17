cmake_minimum_required(VERSION 3.14)

project(SWA)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set (SDL2_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2-2.0.10")

file(GLOB SOURCES "SWA/*.cpp")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SWA SWA/main.cpp)
target_link_libraries(SWA ${SDL2_LIBRARIES})