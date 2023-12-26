// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

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
            if (context.extent < V2i::make_uniform(20))
                throw std::runtime_error("Invalid window size");

            m_clock = std::make_unique<Clock>();
            m_time = m_clock->now();
            m_random = std::make_unique<IntGenerator>();

            m_tileMatrix = std::make_unique<TileMatrix>(context.extent);

            m_player.length = 1;
            m_player.speed = V2f::make_uniform(1.0f);
            m_player.velocity = {0.0f, -m_player.speed.y};
            m_player.position = m_tileMatrix->getCenter();

            for (auto i = 0; i < 20; ++i)
                m_foodPositions.push_back(getRandomFoodPosition());

            updateTileStates();
        }

        void update() override {
            // Draw tiles
            m_tileMatrix->iterate({[&](auto &pos, auto &state) {
                chtype ch;
                switch (state) {
                    case TileState::EMPTY:
                        ch = ' ';
                        break;
                    case TileState::PLAYER_HEAD:
                        ch = 'H';
                        break;
                    case TileState::PLAYER_TAIL:
                        ch = 'T';
                        break;
                    case TileState::PLAYER_BODY:
                        ch = 'B';
                        break;
                    case TileState::FOOD:
                        ch = 'F';
                        break;
                    default:
                        return;
                }
                putCh(ch, pos, m_context);
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
            // Player
            m_tileMatrix->stateAt(m_player.position) = TileState::PLAYER_HEAD;
            // Food
            for (auto &pos: m_foodPositions)
                m_tileMatrix->stateAt(pos) = TileState::FOOD;
        }

        void updateEntityStates() {
            // Check food collision
            auto foodItr = std::find(m_foodPositions.begin(), m_foodPositions.end(), m_player.position);
            if (foodItr != m_foodPositions.end()) {
                // Eat
                ++m_player.length;
                *foodItr = getRandomFoodPosition();
            }

            // Move player
            m_player.position += static_cast<V2i>(m_player.velocity);
        }

        [[nodiscard]] V2i getRandomFoodPosition() const {
            V2i pos = {m_random->dist(1, m_context.extent.x - 1),
                       m_random->dist(1, m_context.extent.y - 1)};
            if (pos.x == m_player.position.x)
                ++pos.x;
            if (pos.y == m_player.position.y)
                ++pos.y;
            return pos;
        }
    };
}// namespace nsnake
