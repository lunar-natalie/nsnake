add_executable(nSnake main.cpp
        App/Context.h
        App/Scene.h
        Application.h
        Game/Clock.h
        Game/Player.h
        Game/TileMatrix.h
        Scenes/Game.h
        Scenes/Menu.h
        Utils/Geometry.h
        Utils/IO.h
        Utils/Random.h
        Utils/Window.h
        Scenes/Kill.h
)
target_include_directories(nSnake
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CURSES_INCLUDE_DIRS})
target_link_libraries(nSnake PRIVATE ${CURSES_LIBRARIES})
target_precompile_headers(nSnake PRIVATE "<curses.h>")
