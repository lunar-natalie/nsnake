// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "Utils/Geometry.h"

namespace nsnake {
    struct ApplicationContext {
        V2i windowExtent{};
        static const int borderWidth = 1;
    };

    struct DrawingContext {
        V2i extent{};
        V2i offset{};
    };
}// namespace nsnake
