add_library(module10)
target_sources(module10 PUBLIC FILE_SET module10 TYPE CXX_MODULES FILES input10.cpp)
target_link_libraries(module10 PUBLIC project_options project_warnings)

add_executable(day10_solution1 solution1.cpp)
target_link_libraries(day10_solution1 PRIVATE module10)

CreateTargetLink(day10_solution1)

add_executable(day10_solution2 solution2.cpp)
target_link_libraries(day10_solution2 PRIVATE module10)
CreateTargetLink(day10_solution2)

