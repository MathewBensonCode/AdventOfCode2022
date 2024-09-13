add_library(day3_common)
target_sources(day3_common PUBLIC FILE_SET CXX_MODULES FILES input3.cpp day3common.cpp)
target_link_libraries(day3_common PUBLIC project_options project_warnings)

add_executable(day3_solution1 solution1.cpp)
target_link_libraries(day3_solution1 PRIVATE day3_common)
CreateTargetLink(day3_solution1)

add_executable(day3_solution2 solution2.cpp)
target_link_libraries(day3_solution2 PRIVATE day3_common)
CreateTargetLink(day3_solution2)

