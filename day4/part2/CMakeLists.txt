add_executable(day4_solution2 solution.cpp)
target_link_libraries(day4_solution2 PRIVATE project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day4/part2/day4_solution2
     ${CMAKE_SOURCE_DIR}/day4/part2/day4_solution2 SYMBOLIC)


