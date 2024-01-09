// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <functional>
#include <map>
#include <memory>

#include "App/Scene.h"
#include "Scenes/Game.h"
#include "Scenes/Menu.h"

namespace nsnake {
    // Map of scene IDs to functions returning class instances
    const std::unordered_map<SceneID, std::function<std::unique_ptr<Scene>(DrawingContext const &context)>> sceneMap = {
            {SceneID::NONE, [](auto &c) { return nullptr; }},
            {SceneID::MENU, [](auto &c) { return std::make_unique<MenuScene>(c); }},
            {SceneID::GAME, [](auto &c) { return std::make_unique<GameScene>(c); }},
    };
}//namespace nsnake
