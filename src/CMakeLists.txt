add_executable(nSnake main.cpp
        App/Context.h
        App/Scene.h
        App/SceneMap.h
        Application.h
        Game/Entities.h
        Game/TileMatrix.h
        Game/Time.h
        Scenes/Game.h
        Scenes/Menu.h
        Utils/Geometry.h
        Utils/IO.h
        Utils/Random.h
        Utils/Window.h
)
target_include_directories(nSnake
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CURSES_INCLUDE_DIRS})
target_link_libraries(nSnake PRIVATE ${CURSES_LIBRARIES})
target_precompile_headers(nSnake PRIVATE "<curses.h>")
