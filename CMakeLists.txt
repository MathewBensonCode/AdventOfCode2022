cmake_minimum_required(VERSION 3.26)

project(AdventOfCode2022 CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

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

#include(cmake/CompileStandardLibraryHeaderUnits.cmake)

if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.27)
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
else ()
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
endif()
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  string(
    CONCAT
      CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE
      "<CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -E -x c++ <SOURCE>"
      " -MT <DYNDEP_FILE> -MD -MF <DEP_FILE>"
      " -fmodules-ts -fdep-file=<DYNDEP_FILE> -fdep-output=<OBJECT> -fdep-format=trtbd"
      " -o <PREPROCESSED_SOURCE>")
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "gcc")
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG
      "-fmodules-ts -fmodule-mapper=<MODULE_MAP_FILE> -fdep-format=trtbd -x c++"
  )
endif()

add_library(std)

#target_sources(std PUBLIC FILE_SET CXX_MODULES FILES standard_library_module.cpp)

#target_link_libraries(std PUBLIC project_options project_warnings)

#add_subdirectory(std.module)

add_subdirectory(fmt)

#target_compile_options(fmt PUBLIC -fmodule-mapper=mapping)

target_link_libraries(project_options INTERFACE std fmt::fmt)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
add_subdirectory(day6)
add_subdirectory(day7)
add_subdirectory(day8)
add_subdirectory(day9)
add_subdirectory(day10)
add_subdirectory(day11)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/compile_commands.json
     ${CMAKE_SOURCE_DIR}/compile_commands.json COPY_ON_ERROR SYMBOLIC)



