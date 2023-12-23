// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <cmath>
#include <memory>

#include "App/Scene.h"
#include "Game/Entities.h"
#include "Game/TileMatrix.h"
#include "Utils/IO.h"

namespace nsnake {
    class GameScene : public Scene {
        std::unique_ptr<TileMatrix> m_tileMatrix;
        Player m_player{};

    public:
        explicit GameScene(const DrawingContext &context)
            : Scene(context, SceneID::GAME) {
            m_tileMatrix = std::make_unique<TileMatrix>(context.extent);
            m_player.headPosition = m_tileMatrix->getCenter();
            m_player.velocity = {0, 1};
            m_player.length = 3;
            updateTileStates();
        }

    private:
        constexpr void updateTileStates() {
            m_tileMatrix->stateAt(m_player.headPosition) = TileState::PLAYER_HEAD;
        }

    public:
        void update() override {
            // Draw tiles
            m_tileMatrix->iterate({[&](auto &pos, auto &state) {
                switch (state) {
                    case TileState::EMPTY:
                        putCh(' ', pos, m_context);
                        break;
                    case TileState::PLAYER_HEAD:
                        putCh(ACS_BLOCK, pos, m_context);
                        break;
                    default:
                        break;
                }
            }});

            // TODO: Update states on clock
            //            m_tileMatrix->reset();
            //            updateEntityStates();
            //            updateTileStates();
        }

        constexpr void updateEntityStates() {
            m_player.headPosition *= static_cast<V2i>(m_player.velocity);
        }

        SceneID processEvent(int ch) override {
            switch (ch) {
                case KEY_RIGHT:
                    m_player.velocity.x = fabs(m_player.velocity.x);
                    break;
                case KEY_LEFT:
                    m_player.velocity.x = -fabs(m_player.velocity.x);
                    break;
                case KEY_UP:
                    m_player.velocity.y = fabs(m_player.velocity.y);
                    break;
                case KEY_DOWN:
                    m_player.velocity.y = -fabs(m_player.velocity.y);
                    break;
                default:
                    break;
            }
            return m_id;
        }
    };
}// namespace nsnake
