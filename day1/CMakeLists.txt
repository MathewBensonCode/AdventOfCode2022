add_executable(day1_solution1)
target_sources(day1_solution1 PRIVATE solution1.cpp PRIVATE FILE_SET HEADERS FILES input1.hpp)
CreateTargetLink(day1_solution1)

add_executable(day1_solution2)
target_sources(day1_solution2 PRIVATE solution2.cpp PRIVATE FILE_SET HEADERS FILES input1.hpp)
CreateTargetLink(day1_solution2)

