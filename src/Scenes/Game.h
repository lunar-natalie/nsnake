// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <chrono>
#include <memory>

#include "App/Scene.h"
#include "Game/Entities.h"
#include "Game/TileMatrix.h"
#include "Utils/IO.h"

namespace chrono = std::chrono;
using namespace std::chrono_literals;

namespace nsnake {
    class GameScene : public Scene {
        using Clock = chrono::steady_clock;

        constexpr static int TARGET_FRAMERATE = 24;

        using FrameDuration = chrono::duration<double, std::ratio<1, TARGET_FRAMERATE>>;
        constexpr static auto ONE_FRAME = FrameDuration(1s);

        std::unique_ptr<TileMatrix> m_tileMatrix;
        std::unique_ptr<Clock> m_clock;
        Clock::time_point m_time;
        Player m_player{};

    public:
        explicit GameScene(const DrawingContext &context)
            : Scene(context, SceneID::GAME) {
            m_tileMatrix = std::make_unique<TileMatrix>(context.extent);

            m_clock = std::make_unique<Clock>();
            m_time = m_clock->now();

            m_player.headPosition = m_tileMatrix->getCenter();
            m_player.maxSpeed = {2.0f, 1.0f};
            m_player.velocity = {0, -m_player.maxSpeed.y};
            m_player.length = 3;

            updateTileStates();
        }

    private:
        constexpr void updateTileStates() {
            m_tileMatrix->stateAt(m_player.headPosition) = TileState::PLAYER_HEAD;
        }

        constexpr void updateEntityStates() {
            m_player.headPosition += static_cast<V2i>(m_player.velocity);
        }

    public:
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
                    m_player.velocity = {m_player.maxSpeed.x, 0.0f};
                    break;
                case KEY_LEFT:
                    m_player.velocity = {-m_player.maxSpeed.x, 0.0f};
                    break;
                case KEY_DOWN:
                    m_player.velocity = {0.0f, m_player.maxSpeed.y};
                    break;
                case KEY_UP:
                    m_player.velocity = {0.0f, -m_player.maxSpeed.y};
                    break;
                default:
                    break;
            }
            return m_id;
        }
    };
}// namespace nsnake
