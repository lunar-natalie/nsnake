// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include "App/Scene.h"
#include "Game/Clock.h"
#include "Game/Player.h"
#include "Game/TileMatrix.h"
#include "Utils/IO.h"
#include "Utils/Random.h"

namespace nsnake {
    class GameScene : public Scene {
        std::unique_ptr<Clock> m_clock;
        Clock::time_point m_time;
        chrono::duration<unsigned, std::milli> m_tickRate = 100ms;

        std::unique_ptr<RandomIntGenerator> m_rng;

        std::unique_ptr<TileMatrix> m_tileMatrix;
        Player m_player;
        std::vector<V2i> m_food;

    public:
        explicit GameScene(const DrawingContext &context) : Scene(context, SceneID::GAME) {
            if (context.extent < V2i::uniform(1))
                throw std::runtime_error("Invalid window size");

            m_clock = std::make_unique<Clock>();
            m_time = m_clock->now();
            m_rng = std::make_unique<RandomIntGenerator>();

            m_tileMatrix = std::make_unique<TileMatrix>(context.extent);
            m_player = Player(m_tileMatrix->getCenter(), 3);

            updateTileStates();

            for (auto i = 0; i < V2i::product(context.extent) / 20; ++i)
                m_food.push_back(randomFoodPosition());
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
            if (FrameDuration(now - m_time) >= FrameDuration(m_tickRate)) {
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
            for (auto &pos: m_food)
                m_tileMatrix->stateAt(pos) = TileState::FOOD;
        }

        void updateEntityStates() {
            // Check food collision
            auto foodItr = std::find(m_food.begin(), m_food.end(), *m_player.head());
            if (foodItr != m_food.end()) {
                m_player.extend();
                *foodItr = randomFoodPosition();
            }

            m_player.updatePosition(m_context);
        }

        [[nodiscard]] V2i randomFoodPosition() const {// Find a random empty tile in the context screen area
            V2i pos;
            do {
                pos = {m_rng->dist(0, m_context.extent.x - 1),
                       m_rng->dist(0, m_context.extent.y - 1)};
            } while (m_tileMatrix->stateAt(pos) != TileState::EMPTY);
            return pos;
        }
    };
}// namespace nsnake
