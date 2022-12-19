add_executable(day8_solution2 solution.cpp)
target_link_libraries(day8_solution2 PRIVATE input8 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day8/part2/day8_solution2
     ${CMAKE_SOURCE_DIR}/day8/part2/day8_solution2 SYMBOLIC)


