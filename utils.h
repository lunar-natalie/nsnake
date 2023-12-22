// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_UTILS_H
#define NSNAKE_UTILS_H

#include <cstring>

#include <curses.h>

#include "context.h"

namespace nsnake {

inline v2i get_extent(WINDOW const* win)
{
    return {.y = getmaxy(win), .x = getmaxx(win)};
}

inline int addstr_center(const char* str, ApplicationContext const& context) noexcept
{
    auto pos = context.window_extent;
    pos.x -= static_cast<int>(std::strlen(str));
    pos /= 2;
    return mvaddstr(pos.y, pos.x, str);
}

}// namespace nsnake

#endif//NSNAKE_UTILS_H
