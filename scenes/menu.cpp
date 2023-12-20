// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include "menu.h"
#include "io.h"

namespace nsnake {

MenuScene::MenuScene(ApplicationContext const& context)
    : Scene(context)
{}

void MenuScene::draw()
{
    addstr_center("Press RETURN to begin", context);
}

SceneId MenuScene::process_event(int ch)
{
    if (ch == '\r') {
        return SceneId::GAME;
    }
    return id;
}

}// namespace nsnake