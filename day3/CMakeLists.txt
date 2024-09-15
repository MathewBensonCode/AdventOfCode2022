add_library(module3)
target_sources(module3 PUBLIC FILE_SET CXX_MODULES FILES input3.cpp module3.cpp)
target_link_libraries(module3 PUBLIC project_options project_warnings)

add_executable(day3_solution1 solution1.cpp)
target_link_libraries(day3_solution1 PRIVATE module3)
CreateTargetLink(day3_solution1)

add_executable(day3_solution2 solution2.cpp)
target_link_libraries(day3_solution2 PRIVATE module3)
CreateTargetLink(day3_solution2)

