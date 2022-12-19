add_library(input8 INTERFACE input8.hpp)
target_include_directories(input8 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(part1)
add_subdirectory(part2)

