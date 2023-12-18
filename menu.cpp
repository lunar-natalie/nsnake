//
// Created by Natalie Wiggins on 17/12/2023.
//

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
        return SceneId::NONE;
    }
    return id;
}

} // nsnake