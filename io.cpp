// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include <cstring>

#include "io.h"
#include "scene.h"

namespace nsnake {

int addstr_center(const char* str, ApplicationContext const& context) noexcept
{
    auto pos = context.window_extent;
    pos.x -= static_cast<int>(std::strlen(str));
    pos /= 2;
    return mvaddstr(pos.y, pos.x, str);
}

}// namespace nsnake