// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <curses.h>

#include "Utils/Geometry.h"

namespace nsnake {
    inline V2i getExtent(const WINDOW *win) {
        return {getmaxx(win), getmaxy(win)};
    }
}// namespace nsnake
