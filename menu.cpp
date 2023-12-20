// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include <cstring>

#include "menu.h"
#include "utils.h"

namespace nsnake {

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