// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_GAME_H
#define NSNAKE_GAME_H

#include "scene.h"

namespace nsnake {

class GameScene : public Scene {
public:
    explicit GameScene(SceneData const * data)
            : Scene(data)
    {}

    void draw() override;
    SceneId process_event(int ch) override;

    const SceneId id = SceneId::GAME;
};

}// namespace nsnake

#endif //NSNAKE_GAME_H
