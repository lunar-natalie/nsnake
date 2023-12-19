// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

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