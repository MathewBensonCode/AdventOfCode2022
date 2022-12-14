add_library(input3 INTERFACE input3.hpp)
target_include_directories(input3 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(part1)
add_subdirectory(part2)

