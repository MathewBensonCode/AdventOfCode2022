find_package(fmt REQUIRED)
add_executable(day11_solution1 solution1.cpp)
target_link_libraries(day11_solution1 PRIVATE fmt::fmt-header-only
                                              project_options project_warnings)
createtargetlink(day11_solution1)

find_package(Boost REQUIRED)

add_executable(day11_solution2 solution2.cpp)
target_include_directories(day11_solution2 PRIVATE Boost::Boost)
target_link_libraries(
  day11_solution2
  PRIVATE
    fmt::fmt-header-only
    project_options
    project_warnings
)
createtargetlink(day11_solution2)
