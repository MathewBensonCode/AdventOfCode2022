add_executable(day1_solution1 solution.cpp)
target_link_libraries(day1_solution1 PRIVATE input1 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day1/part1/day1_solution1
     ${CMAKE_SOURCE_DIR}/day1/part1/day1_solution1 SYMBOLIC)


