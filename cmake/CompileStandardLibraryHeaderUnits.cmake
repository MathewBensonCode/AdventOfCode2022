function(CompileStandardLibraryHeaderUnit header)

    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -std=c++20 -fmodules-ts -fmodule-mapper=mapping -x c++-system-header ${header})
        message("GCC Created Header Unit for => ${header}")

    elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -std=c++20 --precompile -x c++-system-header ${header} -o modules/${header}.pcm)

    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} /std:c++latest /exportHeader /headerName:angle ${header} OUTPUT_VARIABLE cout)
    endif()

endfunction()

function(CreateUseModuleFlags headername)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
        target_compile_options(project_options INTERFACE /headerUnit:angle "${headername}=./${headername}.ifc")
            elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
                target_compile_options(project_options INTERFACE -fmodule-file=${headername}=${CMAKE_CURRENT_BINARY_DIR}/modules/${headername}.pcm)
    endif()

endfunction()

set(SystemHeaders iostream vector memory algorithm iterator string numeric ranges string_view map charconv array sstream cmath cstdint cstring limits utility stdexcept system_error bit bitset)

foreach(headername ${SystemHeaders})
    CompileStandardLibraryHeaderUnit(${headername})
endforeach()

#add -fmodule-ts for gcc
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
target_compile_options(project_options INTERFACE -fmodules-ts -flang-info-include-translate)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
target_compile_options(project_options INTERFACE "/translateInclude")
#elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
#    target_compile_options(project_options INTERFACE -fprebuilt-module-path=${CMAKE_CURRENT_BINARY_DIR})
endif()

foreach(headername ${SystemHeaders})
    CreateUseModuleFlags(${headername}) 
endforeach()
