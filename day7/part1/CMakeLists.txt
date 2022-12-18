add_executable(day7_solution1 solution.cpp)
target_link_libraries(day7_solution1 PRIVATE input7 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day7/part1/day7_solution1
     ${CMAKE_SOURCE_DIR}/day7/part1/day7_solution1 SYMBOLIC)
