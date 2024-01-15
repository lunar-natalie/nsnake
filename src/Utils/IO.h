// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <cstring>

#include <curses.h>

#include "App/Context.h"

namespace nsnake {
    inline int putCh(chtype ch, V2i relativePos, const GraphicsContext &context) noexcept {
        auto finalPos = relativePos + context.offset;
        return mvwaddch(context.window, finalPos.y, finalPos.x, ch);
    }

    inline int putStr(const char *str, V2i relativePos, const GraphicsContext &context) noexcept {
        auto finalPos = relativePos + context.offset;
        return mvwaddstr(context.window, finalPos.y, finalPos.x, str);
    }

    inline int putStrCenter(const char *str, const GraphicsContext &context, int yOffset = 0) noexcept {
        auto pos = context.extent;
        pos.x -= static_cast<int>(std::strlen(str));
        pos /= 2;
        pos.y += yOffset;
        return putStr(str, pos, context);
    }
}// namespace nsnake
