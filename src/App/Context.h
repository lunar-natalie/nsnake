// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <stdexcept>

#include "Utils/Geometry.h"

namespace nsnake {
    struct ApplicationContext {
        V2i windowExtent{};
        static const int borderWidth = 1;
    };

    struct GraphicsContext {
        WINDOW *window{};
        V2i extent{};
        V2i offset{};
    };

    void setWindow(GraphicsContext &context, WINDOW *&win, V2i dimensions) {
        context.window = win;
        context.extent = dimensions;
    }
}// namespace nsnake
