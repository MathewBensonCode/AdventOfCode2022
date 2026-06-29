cmake_minimum_required(VERSION 4.0)

project(AdventOfCode2022 CXX)

# Create Target link on the source directory for convinience
include(cmake/CreateTargetLink.cmake)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/compile_commands.json
     ${CMAKE_SOURCE_DIR}/compile_commands.json COPY_ON_ERROR SYMBOLIC)



