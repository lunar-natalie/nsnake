//
// Created by Natalie Wiggins on 18/12/2023.
//

#include "game.h"
#include "menu.h"
#include "scene.h"

namespace nsnake {

Scene * new_scene(SceneId id, SceneData const * data) noexcept
{
    switch (id) {
        case SceneId::MENU:
            return new MenuScene(data);
        case SceneId::GAME:
            return new GameScene(data);
        default:
            return nullptr;
    }
}

} // nsnake