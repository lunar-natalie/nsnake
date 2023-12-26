// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <curses.h>

#include "App/Context.h"

namespace nsnake {
    inline int putCh(chtype ch, V2i relativePosition, const DrawingContext &context) noexcept {
        auto finalPos = relativePosition + context.offset;
        return mvaddch(finalPos.y, finalPos.x, ch);
    }

    inline int putStr(const char *str, V2i relativePosition, const DrawingContext &context) noexcept {
        auto finalPos = relativePosition + context.offset;
        return mvaddstr(finalPos.y, finalPos.x, str);
    }

    inline int putStrCenter(const char *str, const DrawingContext &context) noexcept {
        auto pos = context.extent;
        pos.x -= static_cast<int>(std::strlen(str));
        pos /= 2;
        return putStr(str, pos, context);
    }
}// namespace nsnake
