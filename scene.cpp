// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include "scene.h"
#include "scenes/game.h"
#include "scenes/menu.h"

namespace nsnake {

Scene* new_scene(SceneId id, ApplicationContext const& context) noexcept
{
    switch (id) {
        case SceneId::MENU:
            return new MenuScene(context);
        case SceneId::GAME:
            return new GameScene(context);
        default:
            return nullptr;
    }
}

}// namespace nsnake