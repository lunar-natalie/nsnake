// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_UTILS_WINDOW_H
#define NSNAKE_UTILS_WINDOW_H

#include <curses.h>

#include "utils/geometry.h"

namespace nsnake {

inline v2i get_extent(WINDOW const* win)
{
    return {.y = getmaxy(win), .x = getmaxx(win)};
}

} //namespace nsnake

#endif //NSNAKE_UTILS_WINDOW_H
