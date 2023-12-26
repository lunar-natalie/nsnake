// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "Utils/Geometry.h"

namespace nsnake {
    struct Player {
        int length;
        V2f speed;
        V2f velocity;
        V2i position;
    };
}// namespace nsnake
