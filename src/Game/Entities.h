// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <list>

#include "Utils/Geometry.h"

namespace nsnake {
    struct Player {
        V2f speed;
        V2f velocity;

        using PosList = std::list<V2i>;
        PosList positions;

        PosList::iterator head() { return positions.begin(); }
        [[nodiscard]] PosList::const_iterator chead() const {
            return positions.begin();
        }
        PosList::iterator body() { return ++positions.begin(); }
        PosList::iterator tail() { return positions.end(); }
    };
}// namespace nsnake
