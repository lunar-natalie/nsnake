// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <memory>
#include <vector>

#include <App/Context.h>
#include <Game/TileMatrix.h>
#include <Utils/Geometry.h>
#include <Utils/Random.h>

namespace nsnake {
    struct Food {
        std::vector<V2i> positions{};
        static const int FREQUENCY = 30;// 1 per every nth tile
    };

    V2i randomFoodPosition(const std::unique_ptr<TileMatrix> &mat, const std::unique_ptr<RandomIntGenerator> &rng, const Context &ctx) {
        V2i pos;
        do {
            pos = {rng->dist(0, ctx.extent.x - 1),
                   rng->dist(0, ctx.extent.y - 1)};
        } while (mat->stateAt(pos) != TileState::EMPTY);
        return pos;
    }
}// namespace nsnake