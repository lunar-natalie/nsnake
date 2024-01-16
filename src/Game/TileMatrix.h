// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <list>
#include <map>
#include <vector>

#include <curses.h>

#include "Utils/Geometry.h"

namespace nsnake {
    enum class TileState {
        EMPTY = 0,// Default value for std::vector
        PLAYER_HEAD,
        PLAYER_BODY,
        PLAYER_TAIL,
        FOOD
    };

    // Iterable 2D vector dividing the screen area into rows and columns of tiles, each storing a TileState.
    class TileMatrix {
        using Columns = std::vector<TileState>;
        using Rows = std::vector<Columns>;

        V2i m_dimensions{};
        Rows m_data{};

    public:
        TileMatrix() = default;

        explicit TileMatrix(V2i dimensions) : m_dimensions{dimensions} {
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

        [[nodiscard]] TileState &stateAt(std::list<V2i>::iterator positionItr) {
            return m_data[positionItr->x][positionItr->y];
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

    // Map of tile states to character data
    const std::map<TileState, chtype> characterMap{
            {TileState::EMPTY, ' '},
            {TileState::PLAYER_HEAD, 'H'},
            {TileState::PLAYER_BODY, 'B'},
            {TileState::PLAYER_TAIL, 'T'},
            {TileState::FOOD, 'F'},
    };
}// namespace nsnake