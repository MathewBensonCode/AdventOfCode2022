add_library(module9)
target_sources(module9 PUBLIC FILE_SET module9 TYPE CXX_MODULES FILES input9.cpp)
target_link_libraries(module9 PRIVATE project_options project_warnings)

add_executable(day9_solution1 solution1.cpp)
target_link_libraries(day9_solution1 PRIVATE module9)
createtargetlink(day9_solution1)

add_executable(day9_solution2 solution2.cpp)
target_link_libraries(day9_solution2 PRIVATE module9)
createtargetlink(day9_solution2)
