// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_SCENES_GAME_H
#define NSNAKE_SCENES_GAME_H

#include "scene.h"

namespace nsnake {

class GameScene : public Scene {
public:
    explicit GameScene(ApplicationContext const& context)
        : Scene(context)
    {}

    void draw() override
    {}

    SceneID process_event(int ch) override
    {
        return id;
    }

    const SceneID id = SceneID::GAME;
};

}// namespace nsnake

#endif//NSNAKE_SCENES_GAME_H
