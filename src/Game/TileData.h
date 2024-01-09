// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <map>

#include <curses.h>

#include "Game/TileMatrix.h"

namespace nsnake {
    // Map of tile states to character data
    const std::map<TileState, chtype> TILE_DATA{
            {TileState::EMPTY, ' '},
            {TileState::PLAYER_HEAD, 'H'},
            {TileState::PLAYER_TAIL, 'T'},
            {TileState::FOOD, 'F'},
    };
}// namespace nsnake