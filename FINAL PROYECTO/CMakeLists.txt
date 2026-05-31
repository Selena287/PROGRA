cmake_minimum_required(VERSION 4.1)
project(FINAL_PROYECTO)

set(CMAKE_CXX_STANDARD 20)

add_executable(FINAL_PROYECTO main.cpp
        ProjectList.cpp
        ProjectList.h
        Student.cpp
        Student.h
        HashTable.cpp
        HashTable.h
        AVL.cpp
        AVL.h
        Graph.cpp
        Graph.h
        Queue.cpp
        Queue.h)
