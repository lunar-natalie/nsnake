// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <list>

#include "App/Context.h"
#include "Utils/Geometry.h"

namespace nsnake {
    struct Player {
        V2f speed = V2f::uniform(1.0f);
        V2f velocity{};

        // Linked list of positions in the tile matrix, each which hold a portion of the snake, starting from the head
        // and ending at the tail.
        using PositionList = std::list<V2i>;
        PositionList positions{};

        PositionList::iterator head() { return positions.begin(); }
        [[nodiscard]] PositionList::const_iterator c_head() const { return positions.cbegin(); }
        PositionList::iterator body() { return ++positions.begin(); /* 2nd element */ }
        PositionList::iterator tail() { return --positions.end(); /* Last element */ }

        explicit Player() = default;

        Player(const V2i &startPos, unsigned length) : velocity{0.0f, -speed.y} {
            positions.push_back(startPos);
            for (auto i = 1; i < length; ++i)
                positions.push_back({c_head()->x, c_head()->y + i});
        }

        void updatePosition(const DrawingContext &dc) {
            auto rawPos = *head() + static_cast<V2i>(velocity);
            auto nextPos = V2i::clamp(rawPos, V2i::uniform(0), dc.extent - V2i::uniform(1));
            if (rawPos == nextPos)
                std::shift_right(positions.begin(), positions.end(), 1);
            *head() = nextPos;
        }

        void extend() {
            auto newTail = *tail();
            if (velocity.x > 0) {
                --newTail.x;
            } else if (velocity.x < 0) {
                ++newTail.x;
            } else if (velocity.y > 0) {
                --newTail.y;
            } else {
                ++newTail.y;
            }
            positions.push_back(newTail);
        }
    };
}// namespace nsnake
