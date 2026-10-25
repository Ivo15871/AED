cmake_minimum_required(VERSION 3.20)
project(Practicas_Gustavo CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Un ejecutable por cada carpeta clase_*
file(GLOB clases RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS "clase_*")
foreach(c ${clases})
    file(GLOB fuentes CONFIGURE_DEPENDS ${c}/*.cpp)
    if(fuentes)
        add_executable(${c} ${fuentes})
    endif()
endforeach()