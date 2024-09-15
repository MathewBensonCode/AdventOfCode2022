add_library(module6)
target_sources(module6 PUBLIC FILE_SET module6 TYPE CXX_MODULES FILES input6.cpp)
target_link_libraries(module6 PUBLIC project_options project_warnings)

add_executable(day6_solution1 solution1.cpp)
target_link_libraries(day6_solution1 PRIVATE module6)
CreateTargetLink(day6_solution1)

add_executable(day6_solution2 solution2.cpp)
target_link_libraries(day6_solution2 PRIVATE module6)
CreateTargetLink(day6_solution2)


