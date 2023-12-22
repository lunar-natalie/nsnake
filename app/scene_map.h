// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_APP_SCENE_MAP_H
#define NSNAKE_APP_SCENE_MAP_H

#include <map>
#include <memory>

#include "app/scene.h"
#include "scenes/game.h"
#include "scenes/menu.h"

namespace nsnake {

// Map of scene IDs to class objects
const std::map<SceneID, std::function<std::unique_ptr<Scene>(ApplicationContext const& context)>> scene_map = {
        {SceneID::NONE, [](auto& context) { return nullptr; }},
        {SceneID::MENU, [](auto& context) { return std::make_unique<MenuScene>(context); }},
        {SceneID::GAME, [](auto& context) { return std::make_unique<GameScene>(context); }},
};

}//namespace nsnake

#endif //NSNAKE_APP_SCENE_MAP_H
