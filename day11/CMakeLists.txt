add_library(module11)
target_sources(module11 PUBLIC FILE_SET module11 TYPE CXX_MODULES FILES input11.cpp)
target_link_libraries(module11 PUBLIC project_options project_warnings)

add_executable(day11_solution1 solution1.cpp)
target_link_libraries(day11_solution1 PRIVATE module11)

CreateTargetLink(day11_solution1)

add_executable(day11_solution2 solution2.cpp)
target_link_libraries(day11_solution2 PRIVATE module11)
CreateTargetLink(day11_solution2)

