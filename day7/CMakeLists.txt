add_library(input7 INTERFACE input7.hpp)
target_include_directories(input7 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(part1)
add_subdirectory(part2)

