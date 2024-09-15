add_library(module5)
target_sources(module5 PUBLIC FILE_SET module5 TYPE CXX_MODULES FILES module5.cpp input5.cpp)
target_link_libraries(module5 PRIVATE project_options project_warnings)

add_executable(day5_solution1 solution1.cpp)
target_link_libraries(day5_solution1 PRIVATE module5)
CreateTargetLink(day5_solution1)

add_executable(day5_solution2 solution2.cpp)
target_link_libraries(day5_solution2 PRIVATE module5)
CreateTargetLink(day5_solution2)

