add_library(module8)
target_sources(module8 PUBLIC FILE_SET module8 TYPE CXX_MODULES FILES input8.cpp module8.cpp)
target_link_libraries(module8 PRIVATE project_options project_warnings)

add_executable(day8_solution1 solution1.cpp)
target_link_libraries(day8_solution1 PRIVATE module8)
CreateTargetLink(day8_solution1)

add_executable(day8_solution2 solution2.cpp)
target_link_libraries(day8_solution2 PRIVATE module8)
CreateTargetLink(day8_solution2)

