add_executable(day7_solution2 solution.cpp)
target_link_libraries(day7_solution2 PRIVATE input7 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day7/part2/day7_solution2
     ${CMAKE_SOURCE_DIR}/day7/part2/day7_solution2 SYMBOLIC)


