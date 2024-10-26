cmake_minimum_required(VERSION 3.10)
project(First_Assignment_Parallel)
set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(First_Assignment_Parallel main.cpp
        src/Boid.cpp
        header/Boid.h
        header/constants.h)

target_link_libraries(First_Assignment_Parallel sfml-graphics sfml-window sfml-system)
