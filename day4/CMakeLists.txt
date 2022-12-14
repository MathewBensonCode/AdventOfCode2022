add_library(input4 INTERFACE input4.hpp)
target_include_directories(input4 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(part1)
add_subdirectory(part2)

