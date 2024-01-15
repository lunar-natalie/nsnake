add_executable(nSnake main.cpp
        App/Context.h
        App/Scene.h
        Application.h
        Game/Clock.h
        Game/Player.h
        Game/TileMatrix.h
        Scenes/GameScene.h
        Scenes/MenuScene.h
        Utils/Geometry.h
        Utils/IO.h
        Utils/Random.h
        Utils/Window.h
        Scenes/KillScene.h
)
target_include_directories(nSnake
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CURSES_INCLUDE_DIRS})
target_link_libraries(nSnake PRIVATE ${CURSES_LIBRARIES} argparse::argparse)
target_precompile_headers(nSnake PRIVATE "<curses.h>")
