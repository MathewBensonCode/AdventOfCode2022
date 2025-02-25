cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

# Set experimental flag to enable `import std` support from CMake. This must be
# enabled before C++ language support.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
    # This specific value changes as experimental support evolves. See
    # `Help/dev/experimental.rst` in the CMake source corresponding to
    # your CMake build for the exact value to use.
       "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
    # "a9e1cf81-9932-4810-974b-6eccaf14e457")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AdventOfCode2022 CXX)


# Tell CMake that we explicitly want `import std`. This will initialize the
# property on all targets declared after this to 1

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE
         "Enable -ftime-trace to generate time tracing .json files on clang"
         OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# Add linker configuration
include(cmake/Linker.cmake)
configure_linker(project_options)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

include(cmake/CreateTargetLink.cmake)

set(CMAKE_CXX_MODULE_STD 1)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
#add_subdirectory(day4)
#add_subdirectory(day5)
add_subdirectory(day6)
add_subdirectory(day7)
add_subdirectory(day8)
add_subdirectory(day9)
add_subdirectory(day10)
add_subdirectory(day11)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/compile_commands.json
     ${CMAKE_SOURCE_DIR}/compile_commands.json COPY_ON_ERROR SYMBOLIC)
