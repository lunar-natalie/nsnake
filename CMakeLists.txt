cmake_minimum_required(VERSION 3.27)
project(nSnake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)
find_package(argparse CONFIG REQUIRED)

add_subdirectory(src)
