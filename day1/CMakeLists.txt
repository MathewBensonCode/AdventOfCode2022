add_executable(day1_solution1 solution1.cpp)
target_link_libraries(day1_solution1 PRIVATE project_options project_warnings)
CreateTargetLink(day1_solution1)

add_executable(day1_solution2 solution2.cpp)
target_link_libraries(day1_solution2 PRIVATE project_options project_warnings)
CreateTargetLink(day1_solution2)
