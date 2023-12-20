// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include "game.h"

namespace nsnake {

GameScene::GameScene(const SceneData * data)
    : Scene(data)
{}

void GameScene::draw()
{
}

SceneId GameScene::process_event(int ch)
{
    return id;
}

}// namespace nsnake