add_library(input9 INTERFACE input9.hpp)
target_include_directories(input9 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(part1)
add_subdirectory(part2)

