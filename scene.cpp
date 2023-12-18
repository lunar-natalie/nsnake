//
// Created by Natalie Wiggins on 18/12/2023.
//

#include "scene.h"
#include "menu.h"

namespace nsnake {

Scene * new_scene(SceneData const * data, SceneId id)
{
    switch (id) {
        case SceneId::MENU:
            return new MenuScene(data);
        default:
            return nullptr;
    }
}

} // nsnake