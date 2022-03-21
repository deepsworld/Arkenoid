# min cmake 
cmake_minimum_required(VERSION 3.0)

# project
project(Arkenoid)

# versions
set (CMAKE_CXX_STANDARD 11)
set (SFML_VER "2.5.1")

# include 
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/external/SFML-${SFML_VER}/include")

# libs
link_directories("${CMAKE_SOURCE_DIR}/external/SFML-${SFML_VER}/lib")

# executable. 
add_executable(arkenoid
    src/main.cpp
)

# link libraries
set(SFML_LIBRARIES libsfml-graphics.so libsfml-window.so libsfml-system.so libsfml-network.so libsfml-audio.so)
target_link_libraries(arkenoid ${SFML_LIBRARIES})