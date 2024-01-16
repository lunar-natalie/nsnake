// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <algorithm>
#include <cmath>
#include <memory>
#include <stdexcept>

#include "App/Scene.h"
#include "Game/Clock.h"
#include "Game/Food.h"
#include "Game/Player.h"
#include "Game/TileMatrix.h"
#include "Utils/Geometry.h"
#include "Utils/IO.h"
#include "Utils/Random.h"

namespace nsnake {
    class GameScene : public Scene {
        WINDOW *m_window;

        std::unique_ptr<Clock> m_clock;
        Clock::time_point m_timeRef;
        TickRate m_tickRate = 100ms;
        static constexpr TickRate MIN_TICK = 50ms;
        static constexpr TickRate TICK_ACCEL = 5ms;

        std::unique_ptr<RandomIntGenerator> m_rng;
        std::unique_ptr<TileMatrix> m_tileMatrix;

        Player m_player;
        Food m_food;

    public:
        explicit GameScene(Context &ctx)
            : Scene(ctx, SceneID::GAME, SceneFlags::SUBWIN | SceneFlags::BORDER) {
            // Create fullscreen window
            if (auto win = subwin(stdscr, 0, 0, 0, 0); win != nullptr) {
                m_window = win;
            } else {
                throw std::runtime_error("Failed to create game window");
            }
            setWindow(m_context, m_window);
            if (V2i::product(m_context.extent) < std::pow(Player::MIN_LENGTH, 2))
                throw std::runtime_error("Invalid window size");

            // Initialize objects
            m_clock = std::make_unique<Clock>();
            m_timeRef = m_clock->now();
            m_rng = std::make_unique<RandomIntGenerator>();
            m_tileMatrix = std::make_unique<TileMatrix>(m_context.extent);

            // Initialize entities
            initPlayer(m_player, m_tileMatrix->getCenter());
            updateTileStates();
            for (auto i = 0; i < V2i::product(m_context.extent) / Food::FREQUENCY; ++i)
                m_food.positions.push_back(randomFoodPosition(m_tileMatrix, m_rng, m_context));
        }

        void update() override {
            // Draw tiles
            m_tileMatrix->iterate({[&](auto &pos, auto &state) {
                // Place the character corresponding to the tile state
                if (auto el = characterMap.find(state); el != characterMap.end())
                    putCh(el->second, pos, m_context);
            }});

            // Update states on tick
            auto now = m_clock->now();
            if (FrameDuration(now - m_timeRef) >= FrameDuration(m_tickRate)) {
                m_tileMatrix->reset();
                updateEntityStates();
                updateTileStates();
                m_timeRef = now;
            }
        }

        SceneID processEvent(int ch) override {
            if (!m_player.isAlive)
                // Game over
                return SceneID::KILL;
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
        // Sets character data in the tile matrix
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
            for (auto &pos: m_food.positions)
                m_tileMatrix->stateAt(pos) = TileState::FOOD;
        }

        // Handles entity logic
        void updateEntityStates() {
            // Check player collision
            auto playerItr = std::find(m_player.body(), m_player.positions.end(), *m_player.head());
            if (playerItr != m_player.positions.end())
                m_player.isAlive = false;

            // Check food collision
            auto foodItr = std::find(m_food.positions.begin(), m_food.positions.end(), *m_player.head());
            if (foodItr != m_food.positions.end()) {
                extendPlayer(m_player);
                // Replace with new food item
                *foodItr = randomFoodPosition(m_tileMatrix, m_rng, m_context);
                // Accelerate
                if (m_tickRate > MIN_TICK)
                    m_tickRate = std::max(m_tickRate - TICK_ACCEL, MIN_TICK);
            }

            // Move player
            updatePlayerPosition(m_player, m_context);
        }

    public:
        ~GameScene() override {
            delwin(m_window);
        }
    };
}// namespace nsnake
