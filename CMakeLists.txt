cmake_minimum_required(VERSION 3.17)
project(sfml_0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O2")

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

file(GLOB ALL_REQUIRED_DLL "SFML-2.5.1/bin/*.dll")
file(COPY ${ALL_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "Images" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "Audio" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "Fonts" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(MAKE_DIRECTORY Highscore)
file(COPY "Highscore" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


file(GLOB SOURCES
        *.hpp
        *.cpp
        Levels/*.hpp
        Levels/*.cpp)

add_executable(sfml_0 ${SOURCES})

find_package(SFML COMPONENTS graphics audio window REQUIRED)
#find_library(SFML ,${SFML_DIR})
target_link_libraries(sfml_0 sfml-graphics sfml-audio sfml-window)

