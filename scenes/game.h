// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_SCENES_GAME_H
#define NSNAKE_SCENES_GAME_H

#include "scene.h"

namespace nsnake {

class GameScene : public Scene {
public:
    explicit GameScene(ApplicationContext const& context);

    void draw() override;
    SceneId process_event(int ch) override;

    const SceneId id = SceneId::GAME;
};

}// namespace nsnake

#endif//NSNAKE_SCENES_GAME_H
