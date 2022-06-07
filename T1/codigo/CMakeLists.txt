cmake_minimum_required(VERSION 3.21)
project(DA_PROJ1)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_PROJ1
        main.cpp
        include/Application.h
        include/Starter.h
        include/Truck.h
        include/ReadFiles.h
        include/Menu.h
        include/Order.h
        include/Cargo.h
        src/Starter.cpp
        src/Application.cpp
        src/Menu.cpp
        src/ReadFiles.cpp
        src/Order.cpp
        src/Truck.cpp
        src/Cargo.cpp
        )

target_link_libraries(DA_PROJ1)