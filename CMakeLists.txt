# vim: ft=cmake:et:ts=4:ff=unix:fenc=utf-8:
cmake_minimum_required(VERSION 3.0.2)

project(_init_ C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

#include(FindPkgConfig)
#pkg_check_modules(GL REQUIRED gl glu)
include(FindOpenGL)
include(FindGLUT)

if (${GLUT_FOUND})
    set(GL_LIBRARIES ${GL_LIBRARIES} ${GLUT_glut_LIBRARY})
    set(GL_INCLUDE_DIRS ${GL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})
else () 
    message(FATAL_ERROR "glut library not found")
endif()

if (${OPENGL_FOUND})
    if (NOT ${OPENGL_GLU_FOUND})
        message(FATAL_ERROR "glu library not found")
    endif()

    set(GL_LIBRARIES ${GL_LIBRARIES}
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY})

    set(GL_INCLUDE_DIRS ${GL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
else ()
    message(FATAL_ERROR "OpenGL not found")
endif()

message(STATUS "GL_LIBRARIES: ${GL_LIBRARIES}")
message(STATUS "GL_INCLUDE_DIRS: ${GL_INCLUDE_DIRS}")
message(STATUS "GL_LIBRARY_DIRS: ${GL_LIBRARY_DIRS}")

if (CMAKE_COMPILER_IS_GNUCC)                                                    
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic -D_DEFAULT_SOURCE")
endif ()                                                                        

link_directories(
    ${GL_LIBRARY_DIRS}
    )

include_directories(
    src/lib
    ${GL_INCLUDE_DIRS}
    )

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

target_link_libraries(test_nurbs
    nrk
    m
    ${GL_LIBRARIES}
    )

# *** main
project(norkkie C)
add_executable(norkkie src/main/main.c
    src/main/msel.c
    src/main/input.c
    src/main/msel_func_model.c
    src/main/msel_func_root.c
    src/main/msel_func.c
    )

target_link_libraries(norkkie
    nrk
    m
    ${GL_LIBRARIES}
    )

