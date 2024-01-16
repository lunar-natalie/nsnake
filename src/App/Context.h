// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <stdexcept>

#include <curses.h>

#include "Utils/Geometry.h"
#include "Utils/Window.h"

namespace nsnake {
    struct Context {
        WINDOW *window{};
        V2i extent{};
        V2i offset{};
        static const int BORDER_WIDTH = 1;
    };

    constexpr void setWindow(Context &ctx, WINDOW *win) {
        auto border = V2i::uniform(Context::BORDER_WIDTH);
        ctx.window = win;
        ctx.extent = getExtent(win) - (2 * border);
        ctx.offset = border;
    }
}// namespace nsnake
