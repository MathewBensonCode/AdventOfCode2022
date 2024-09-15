add_library(module7)
target_sources(module7 PUBLIC FILE_SET module7 TYPE CXX_MODULES FILES input7.cpp module7.cpp)
target_link_libraries(module7 PUBLIC project_options project_warnings)

add_executable(day7_solution1 solution1.cpp)
target_link_libraries(day7_solution1 PRIVATE module7)
CreateTargetLink(day7_solution1)

add_executable(day7_solution2 solution2.cpp)
target_link_libraries(day7_solution2 PRIVATE module7)
CreateTargetLink(day7_solution2)


