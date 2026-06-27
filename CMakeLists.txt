cmake_minimum_required(VERSION 4.0 FATAL_ERROR)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
    # This specific value changes as experimental support evolves. See
    # `Help/dev/experimental.rst` in the CMake source corresponding to
    # your CMake build for the exact value to use.
    # old version   "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
    #"a9e1cf81-9932-4810-974b-6eccaf14e457")
    "d0edc3af-4c50-42ea-a356-e2862fe7a444")

project(AdventOfCode2022 CXX)

include(cmake/CreateTargetLink.cmake)


set(CMAKE_CXX_MODULE_STD 1)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
add_subdirectory(day6)
add_subdirectory(day7)
add_subdirectory(day8)
add_subdirectory(day9)
add_subdirectory(day10)
add_subdirectory(day11)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/compile_commands.json
     ${CMAKE_SOURCE_DIR}/compile_commands.json COPY_ON_ERROR SYMBOLIC)
