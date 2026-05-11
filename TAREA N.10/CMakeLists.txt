cmake_minimum_required(VERSION 3.10) # Version 4.1 is likely a typo; standard is 3.x
project(TAREA_N_10)

set(CMAKE_CXX_STANDARD 20)

# Remove the 'main.cpp' that isn't inside src/
add_executable(TAREA_N_10 
        src/main.cpp
        src/avl.cpp
        src/avl.h
        src/student.h)