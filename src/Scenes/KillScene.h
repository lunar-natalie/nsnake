// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <curses.h>

#include <App/Scene.h>
#include <Utils/IO.h>

namespace nsnake {
    class KillScene : public Scene {
        WINDOW *m_overlay;

    public:
        explicit KillScene(const GraphicsContext &context)
            : Scene(context, SceneID::KILL, SceneFlags::SUBWIN) {// Implicit no redraw
            m_overlay = subwin(stdscr, m_context.extent.y, m_context.extent.x, 0, 0);
        }

        void update() override {
            putStrCenter("GAME OVER", m_context, -1, m_overlay);
            putStrCenter("Press RETURN to play again", m_context, 1, m_overlay);
        }

        SceneID processEvent(int ch) override {
            if (ch == '\r')
                return SceneID::GAME;
            return m_id;
        }

        ~KillScene() override {
            delwin(m_overlay);
        }
    };
}// namespace nsnake