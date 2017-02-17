# vim: ft=cmake:et:ts=4:ff=unix:fenc=utf-8:
cmake_minimum_required(VERSION 3.0.2)

project(_init_ C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

if (CMAKE_COMPILER_IS_GNUCC)                                                    
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic -D_DEFAULT_SOURCE")
endif ()                                                                        

include_directories(src/lib)

# *** library
project(nrk C)
add_library(nrk SHARED
    src/lib/norkkie/src/nurbs.c
    src/lib/norkkie/src/nurbs.c
    src/lib/norkkie/src/pack_tools.c
    )

# *** test
project(test_nurbs C)
add_executable(test_nurbs
    src/test/nurbs/main.c
    )
target_link_libraries(test_nurbs nrk m GL GLU glut)

# *** main
project(norkkie C)
add_executable(norkkie src/main/main.c
    src/main/msel.c
    src/main/input.c
    src/main/msel_func_model.c
    src/main/msel_func_root.c
    src/main/msel_func.c
    )
target_link_libraries(norkkie nrk m GL GLU glut)

