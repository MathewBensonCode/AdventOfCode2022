find_package(fmt REQUIRED)
add_executable(day9_solution1 solution.cpp)
target_link_libraries(day9_solution1 PRIVATE input9 fmt::fmt-header-only project_options
                                             project_warnings)

CreateTargetLink(day9_solution1)
