add_executable(day1_solution2 solution.cpp)
target_link_libraries(day1_solution2 PRIVATE input1 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day1/part2/day1_solution2
     ${CMAKE_SOURCE_DIR}/day1/part2/day1_solution2 SYMBOLIC)


