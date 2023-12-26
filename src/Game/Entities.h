// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "Utils/Geometry.h"

namespace nsnake {
    struct Player {
        V2i position;
        V2f velocity;
        V2f speed;
        int length;
    };
}// namespace nsnake
