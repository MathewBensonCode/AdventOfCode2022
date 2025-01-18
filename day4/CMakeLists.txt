add_library(modules4)
target_sources(modules4 PUBLIC FILE_SET modules4 TYPE CXX_MODULES FILES input4.cpp module4.cpp)
target_link_libraries(modules4 PUBLIC project_options project_warnings)

add_executable(day4_solution1 solution1.cpp)
target_link_libraries(day4_solution1 PRIVATE modules4)
CreateTargetLink(day4_solution1)

add_executable(day4_solution2 solution2.cpp)
target_link_libraries(day4_solution2 PRIVATE modules4)
CreateTargetLink(day4_solution2)

