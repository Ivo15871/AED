include(FetchContent)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

add_executable(clase_6 main.cpp "graficarArbol.h" "cTree.h")
target_link_libraries(clase_6 PRIVATE SFML::Graphics)