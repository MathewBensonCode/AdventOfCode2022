add_library(input1 INTERFACE input1.hpp)
target_include_directories(input1 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(part1)
add_subdirectory(part2)

