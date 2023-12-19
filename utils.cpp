// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include <cstring>

#include "utils.h"
#include "scene.h"

namespace nsnake {

int addstr_center(const char * str, SceneData const * scene_data) noexcept
{
    auto pos = scene_data->window_extent;
    pos.x -= static_cast<int>(std::strlen(str));
    pos /= 2;
    return mvaddstr(pos.y, pos.x, str);
}

} // nsnake