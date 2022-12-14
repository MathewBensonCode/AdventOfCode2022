add_executable(day2_solution1 solution.cpp)
target_link_libraries(day2_solution1 PRIVATE input2 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day2/part1/day2_solution1
     ${CMAKE_SOURCE_DIR}/day2/part1/day2_solution1 SYMBOLIC)


