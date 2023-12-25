// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <vector>

#include "Utils/Geometry.h"

namespace nsnake {
    enum class TileState {
        EMPTY = 0,
        PLAYER_HEAD,
        PLAYER_TAIL,
        PLAYER_BODY,
        FOOD
    };

    class TileMatrix {
        using Columns = std::vector<TileState>;
        using Rows = std::vector<Columns>;

        V2i m_dimensions{};
        Rows m_data{};

    public:
        TileMatrix() = default;

        explicit TileMatrix(V2i dimensions) : m_dimensions{dimensions} {
            // Initialize 2D state vector to 0 (TileState::EMPTY) with the specified dimensions
            m_data = std::vector(dimensions.x, std::vector<TileState>(dimensions.y));
        }

        constexpr void reset() {
            std::fill(m_data.begin(), m_data.end(), std::vector<TileState>(m_dimensions.x, TileState::EMPTY));
        }

        [[nodiscard]] constexpr V2i getCenter() const {
            return static_cast<V2i>(m_dimensions / 2);
        }

        [[nodiscard]] constexpr TileState &stateAt(V2i position) {
            return m_data[position.x][position.y];
        }

        constexpr void iterate(const std::function<void(const V2i &position, const TileState &state)> &callback) {
            Rows::iterator rowItr;
            Columns::iterator colItr;
            V2i pos;
            for (rowItr = m_data.begin(), pos.x = 0; rowItr != m_data.end(); ++rowItr, ++pos.x) {
                for (colItr = rowItr->begin(), pos.y = 0; colItr != rowItr->end(); ++colItr, ++pos.y)
                    callback(pos, *colItr);
            }
        }
    };
}// namespace nsnake