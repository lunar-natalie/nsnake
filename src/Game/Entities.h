// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "Utils/Geometry.h"

namespace nsnake {
    struct Player {
        V2i headPosition;
        V2i tailPosition;
        V2f maxSpeed;
        V2f velocity;
        int length;
    };
}// namespace nsnake
