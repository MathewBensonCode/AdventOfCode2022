add_executable(day8_solution1 solution1.cpp)
target_link_libraries(day8_solution1 PRIVATE project_options project_warnings)
CreateTargetLink(day8_solution1)

find_package(TBB REQUIRED COMPONENTS tbb)
add_executable(day8_solution2 solution2.cpp)
target_link_libraries(day8_solution2 PRIVATE project_options project_warnings tbb)
CreateTargetLink(day8_solution2)

