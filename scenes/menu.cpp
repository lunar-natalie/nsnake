// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include "menu.h"
#include "utils.h"

namespace nsnake {

MenuScene::MenuScene(SceneData const * data)
    : Scene(data)
{}

void MenuScene::draw()
{
    addstr_center("Press RETURN to begin", data);
}

SceneId MenuScene::process_event(int ch)
{
    if (ch == '\r') {
        return SceneId::GAME;
    }
    return id;
}

}// namespace nsnake