cmake_minimum_required(VERSION 3.27)
project(nSnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

add_subdirectory(src)
