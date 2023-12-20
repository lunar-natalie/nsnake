// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include "game.h"

namespace nsnake {

GameScene::GameScene(ApplicationContext const& context)
    : Scene(context)
{}

void GameScene::draw()
{
}

SceneId GameScene::process_event(int ch)
{
    //    switch (ch) {
    //        case KEY_RIGHT:
    //            player.vel.x = 1;
    //            break;
    //        case KEY_LEFT:
    //            player.vel.x = -1;
    //            break;
    //        case KEY_UP:
    //            player.vel.y = 1;
    //            break;
    //        case KEY_DOWN:
    //            player.vel.y = -1;
    //            break;
    //    }
    return id;
}

}// namespace nsnake