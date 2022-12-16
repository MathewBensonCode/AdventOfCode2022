add_executable(day5_solution2 solution.cpp)
target_link_libraries(day5_solution2 PRIVATE input5 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day5/part2/day5_solution2
     ${CMAKE_SOURCE_DIR}/day5/part2/day5_solution2 SYMBOLIC)


