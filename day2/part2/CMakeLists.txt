add_executable(day2_solution2 solution.cpp)
target_link_libraries(day2_solution2 PRIVATE input2 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day2/part2/day2_solution2
     ${CMAKE_SOURCE_DIR}/day2/part2/day2_solution2 SYMBOLIC)


