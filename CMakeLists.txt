cmake_minimum_required(VERSION 3.5)

project(cours1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cours1 main.cpp)

install(TARGETS cours1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
