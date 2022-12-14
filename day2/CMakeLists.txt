add_library(input2 INTERFACE input2.hpp)
target_include_directories(input2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(part1)
add_subdirectory(part2)

