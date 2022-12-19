add_executable(day8_solution1 solution.cpp)
target_link_libraries(day8_solution1 PRIVATE input8 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day8/part1/day8_solution1
     ${CMAKE_SOURCE_DIR}/day8/part1/day8_solution1 SYMBOLIC)
