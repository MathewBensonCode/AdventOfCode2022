add_executable(day4_solution1 solution.cpp)
target_link_libraries(day4_solution1 PRIVATE input4 project_options project_warnings)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/day4/part1/day4_solution1
     ${CMAKE_SOURCE_DIR}/day4/part1/day4_solution1 SYMBOLIC)
