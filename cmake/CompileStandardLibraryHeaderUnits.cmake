function(CompileStandardLibraryHeaderUnit header)

    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -std=c++20 -fmodules-ts -x c++-system-header ${header})
        message("GCC Created Header Unit for => ${header}")

    elseif(${CMAKE_CXX_COMPILER_ID} MATCHES ".*Clang")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} "-std=c++20 --precompile -x c++-system-header ${header}")

    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} "/std:c++latest /exportHeader /headerName:angle ${header}")
    endif()

    message("Compiled Header Unit for => ${header}")

endfunction()


set(SystemHeaders iostream vector memory algorithm iterator string_view numeric)

foreach(headername ${SystemHeaders})
    CompileStandardLibraryHeaderUnit(${headername})
endforeach()
