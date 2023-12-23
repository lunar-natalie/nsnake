// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <functional>
#include <map>
#include <memory>

#include "Scene.h"
#include "Scenes/Game.h"
#include "Scenes/Menu.h"

namespace nsnake {
    // World of scene IDs to class objects
    const std::map<SceneID, std::function<std::unique_ptr<Scene>(DrawingContext const &context)>> sceneMap = {
            {SceneID::NONE, [](auto &ctx) { return nullptr; }},
            {SceneID::MENU, [](auto &ctx) { return std::make_unique<MenuScene>(ctx); }},
            {SceneID::GAME, [](auto &ctx) { return std::make_unique<GameScene>(ctx); }},
    };
}//namespace nsnake
