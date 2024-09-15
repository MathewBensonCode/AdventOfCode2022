add_library(module2)
target_sources(module2 PUBLIC FILE_SET modules2 TYPE CXX_MODULES FILES input2.cpp )
target_link_libraries(module2 PUBLIC project_options project_warnings)

add_executable(day2_solution1 solution1.cpp)
target_link_libraries(day2_solution1 PRIVATE module2)
CreateTargetLink(day2_solution1)

add_executable(day2_solution2 solution2.cpp)
target_link_libraries(day2_solution2 PRIVATE module2)
CreateTargetLink(day2_solution2)


