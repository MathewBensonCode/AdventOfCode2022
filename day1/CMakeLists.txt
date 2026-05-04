add_executable(day1_solution1)
target_sources(day1_solution1 PRIVATE solution1.cpp utility.cpp
  PRIVATE FILE_SET HEADERS BASE_DIRS .)
target_link_libraries(day1_solution1 PRIVATE TBB::tbb)
CreateTargetLink(day1_solution1)

add_executable(day1_solution2 solution2.cpp)
CreateTargetLink(day1_solution2)

