// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include "App/Scene.h"
#include "Game/Entities.h"
#include "Game/TileMatrix.h"
#include "Game/Time.h"
#include "Utils/IO.h"
#include "Utils/Random.h"

namespace nsnake {
    class GameScene : public Scene {
        std::unique_ptr<Clock> m_clock;
        Clock::time_point m_time;
        std::unique_ptr<IntGenerator> m_random;

        std::unique_ptr<TileMatrix> m_tileMatrix;
        Player m_player{};
        std::vector<V2i> m_foodPositions{};

    public:
        explicit GameScene(const DrawingContext &context) : Scene(context, SceneID::GAME) {
            if (context.extent < V2i::uniform(1))
                throw std::runtime_error("Invalid window size");

            // Initialize utils
            m_clock = std::make_unique<Clock>();
            m_time = m_clock->now();
            m_random = std::make_unique<IntGenerator>();
            m_tileMatrix = std::make_unique<TileMatrix>(context.extent);

            // Initialize player
            m_player.speed = V2f::uniform(1.0f);
            m_player.velocity = {0.0f, -m_player.speed.y};
            m_player.positions.push_back(m_tileMatrix->getCenter());
            for (auto i = 1; i < 3; ++i)
                m_player.positions.push_back({m_player.c_head()->x, m_player.c_head()->y + i});

            // Add food
            for (auto i = 0; i < 20; ++i)
                m_foodPositions.push_back(getRandomFoodPosition());

            updateTileStates();
        }

        void update() override {
            // Draw tiles
            m_tileMatrix->iterate({[&](auto &pos, auto &state) {
                // Put the character corresponding to the tile state at the tile position
                if (auto el = characterMap.find(state); el != characterMap.end())
                    putCh(el->second, pos, m_context);
            }});

            // Update states on frame clock
            auto now = m_clock->now();
            if (FrameDuration(now - m_time) >= ONE_FRAME) {
                m_tileMatrix->reset();
                updateEntityStates();
                updateTileStates();
                m_time = now;
            }
        }

        SceneID processEvent(int ch) override {
            switch (ch) {
                // Movement
                case KEY_RIGHT:
                    m_player.velocity = {m_player.speed.x, 0.0f};
                    break;
                case KEY_LEFT:
                    m_player.velocity = {-m_player.speed.x, 0.0f};
                    break;
                case KEY_DOWN:
                    m_player.velocity = {0.0f, m_player.speed.y};
                    break;
                case KEY_UP:
                    m_player.velocity = {0.0f, -m_player.speed.y};
                    break;
                default:
                    break;
            }
            return m_id;
        }

    private:
        void updateTileStates() {
            // Set player tiles
            m_tileMatrix->stateAt(m_player.head()) = TileState::PLAYER_HEAD;
            auto bodyItr = m_player.body();
            do {
                m_tileMatrix->stateAt(bodyItr) = TileState::PLAYER_BODY;
                ++bodyItr;
            } while (bodyItr != m_player.tail());
            m_tileMatrix->stateAt(m_player.tail()) = TileState::PLAYER_TAIL;

            // Set food tiles
            for (auto &pos: m_foodPositions)
                m_tileMatrix->stateAt(pos) = TileState::FOOD;
        }

        void updateEntityStates() {
            // Check food collision
            auto foodItr = std::find(m_foodPositions.begin(), m_foodPositions.end(), *m_player.head());
            if (foodItr != m_foodPositions.end()) {
                // TODO: Extend player
                // Replace with new food item
                *foodItr = getRandomFoodPosition();
            }

            // Move player
            auto rawPos = *m_player.head() + static_cast<V2i>(m_player.velocity);
            auto nextPos = V2i::clamp(rawPos, V2i::uniform(0), m_context.extent - V2i::uniform(1));
            if (rawPos == nextPos)
                std::shift_right(m_player.positions.begin(), m_player.positions.end(), 1);
            *m_player.head() = nextPos;
        }

        [[nodiscard]] V2i getRandomFoodPosition() const {
            V2i pos;
            do {
                pos = {m_random->dist(0, m_context.extent.x - 1),
                       m_random->dist(0, m_context.extent.y - 1)};
            } while (m_tileMatrix->stateAt(pos) != TileState::EMPTY);
            return pos;
        }
    };
}// namespace nsnake
