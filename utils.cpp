//
// Created by Natalie Wiggins on 18/12/2023.
//

#include <cstring>

#include "utils.h"
#include "scene.h"

namespace nsnake {

int addstr_center(const char * str, SceneData const * scene_data)
{
    auto pos = scene_data->window_extent;
    pos.x -= static_cast<int>(std::strlen(str));
    pos /= 2;
    return mvaddstr(pos.y, pos.x, str);
}

} // nsnake