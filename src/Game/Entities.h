// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <list>

#include "Utils/Geometry.h"

namespace nsnake {
    struct Player {
        V2f speed;
        V2f velocity;

        // Linked list of positions in the tile matrix, each which hold a portion of the snake, starting from the head
        // and ending at the tail.
        using PosList = std::list<V2i>;
        PosList positions;

        PosList::iterator head() { return positions.begin(); }
        [[nodiscard]] PosList::const_iterator cHead() const {
            return positions.begin();
        }
        PosList::iterator body() { return ++positions.begin(); }
        PosList::iterator tail() { return positions.end(); }
    };
}// namespace nsnake
