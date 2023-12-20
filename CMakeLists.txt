cmake_minimum_required(VERSION 3.27)
project(nSnake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

add_executable(nSnake main.cpp
        application.cpp
        application.h
        geometry.h
        scene.h
        scenes/menu.cpp
        scenes/menu.h
        scene.cpp
        io.h
        io.cpp
        scenes/game.cpp
        scenes/game.h
        context.h
)
target_include_directories(nSnake
        PRIVATE ${CMAKE_SOURCE_DIR} ${CURSES_INCLUDE_DIRS})
target_link_libraries(nSnake PRIVATE ${CURSES_LIBRARIES})
target_precompile_headers(nSnake PRIVATE "<curses.h>")
