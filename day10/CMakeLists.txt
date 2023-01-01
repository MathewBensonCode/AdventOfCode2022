find_package(fmt REQUIRED)
add_executable(day10_solution1 solution1.cpp)
target_link_libraries(day10_solution1 PRIVATE fmt::fmt-header-only project_options
                                             project_warnings)
CreateTargetLink(day10_solution1)

add_executable(day10_solution2 solution2.cpp)
target_link_libraries(day10_solution2 PRIVATE fmt::fmt-header-only project_options
                                             project_warnings)
CreateTargetLink(day10_solution2)

