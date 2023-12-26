// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <curses.h>

#include "Utils/Geometry.h"

namespace nsnake {
    inline V2i getExtent(const WINDOW *window) {
        return {getmaxx(window), getmaxy(window)};
    }
}// namespace nsnake
