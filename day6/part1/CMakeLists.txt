add_executable(day6_solution1 solution.cpp)
target_link_libraries(day6_solution1 PRIVATE input6 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day6/part1/day6_solution1
     ${CMAKE_SOURCE_DIR}/day6/part1/day6_solution1 SYMBOLIC)
