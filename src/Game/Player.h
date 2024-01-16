// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <list>

#include "App/Context.h"
#include "Utils/Geometry.h"

namespace nsnake {
    struct Player {
        static const int MIN_LENGTH = 3;
        V2f speed = V2f::uniform(1.0f);
        V2f velocity{};
        bool isAlive = true;

        // Linked list of positions in the tile matrix, each which hold a portion of the snake, starting from the head
        // and ending at the tail.
        using PositionList = std::list<V2i>;
        PositionList positions{};

        PositionList::iterator head() { return positions.begin(); }
        [[nodiscard]] PositionList::const_iterator c_head() const { return positions.cbegin(); }
        PositionList::iterator body() { return ++positions.begin(); /* 2nd element */ }
        PositionList::iterator tail() { return --positions.end(); /* Last element */ }
    };

    void initPlayer(Player &player, const V2i &startPos, int length = Player::MIN_LENGTH) {
        // Set the default upwards velocity
        player.velocity = {0.0f, -player.speed.y};
        // Push the initial head, body and tail positions, extending from the default direction (down)
        player.positions.push_back(startPos);
        for (auto i = 1; i < length; ++i)
            player.positions.push_back({player.c_head()->x, player.c_head()->y + i});
    }

    void updatePlayerPosition(Player &player, const Context &ctx) {
        // Get next position
        auto rawPos = *player.head() + static_cast<V2i>(player.velocity);
        // Cap position to matrix area
        auto nextPos = V2i::clamp(rawPos, V2i::uniform(0), ctx.extent - V2i::uniform(1));
        // Increment body and tail positions
        if (rawPos == nextPos)
            std::shift_right(player.positions.begin(), player.positions.end(), 1);
        // Set new head position
        *player.head() = nextPos;
    }

    void extendPlayer(Player &player) {
        auto newTail = *player.tail();
        // Adjust new position in reverse direction to movement
        if (player.velocity.x > 0) {
            --newTail.x;// Up
        } else if (player.velocity.x < 0) {
            ++newTail.x;// Down
        } else if (player.velocity.y > 0) {
            --newTail.y;// Left
        } else {
            ++newTail.y;// Right
        }
        player.positions.push_back(newTail);
    }
}// namespace nsnake
