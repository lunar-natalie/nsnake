// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <App/Scene.h>
#include <Utils/IO.h>

namespace nsnake {
    class KillScene : public Scene {
    public:
        explicit KillScene(const DrawingContext &context) : Scene(context, SceneID::KILL) {}

        void update() override {
            putStrCenter("GAME OVER", m_context, -1);
            putStrCenter("Press RETURN to play again", m_context, 1);
        }

        SceneID processEvent(int ch) override {
            if (ch == '\r')
                return SceneID::GAME;
            return m_id;
        }
    };
}// namespace nsnake