add_library(day1lib)
target_sources(day1lib PUBLIC FILE_SET CXX_MODULES FILES day1lib.cpp)
target_link_libraries(day1lib PUBLIC project_options project_warnings)

add_executable(day1_solution1 solution1.cpp)
target_link_libraries(day1_solution1 PRIVATE day1lib)
CreateTargetLink(day1_solution1)

add_executable(day1_solution2 solution2.cpp)
target_link_libraries(day1_solution2 PRIVATE day1lib)
CreateTargetLink(day1_solution2)
