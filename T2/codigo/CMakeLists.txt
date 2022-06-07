cmake_minimum_required(VERSION 3.21)
project(FEUP_DA2)

set(CMAKE_CXX_STANDARD 14)

add_executable(FEUP_DA2 main.cpp src/graph.cpp include/graph.h src/ReadFiles.cpp include/ReadFiles.h src/Starter.cpp include/Starter.h src/Menu.cpp include/Menu.h src/Application.cpp include/Application.h include/MaxHeap.h)
