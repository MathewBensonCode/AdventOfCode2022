add_executable(day1_solution1)
target_include_directories(day1_solution1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(day1_solution1 PRIVATE solution1.cpp utility.cpp)
target_link_libraries(day1_solution1 PRIVATE project_options project_warnings TBB::tbb)
CreateTargetLink(day1_solution1)

add_executable(day1_solution2 solution2.cpp)
target_link_libraries(day1_solution2 PRIVATE project_options project_warnings)
CreateTargetLink(day1_solution2)

