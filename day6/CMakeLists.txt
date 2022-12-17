add_library(input6 INTERFACE input6.hpp)
target_include_directories(input6 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(part1)
add_subdirectory(part2)

