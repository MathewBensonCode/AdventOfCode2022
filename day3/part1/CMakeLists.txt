add_executable(day3_solution1 solution.cpp)
target_link_libraries(day3_solution1 PRIVATE input3 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day3/part1/day3_solution1
     ${CMAKE_SOURCE_DIR}/day3/part1/day3_solution1 SYMBOLIC)
