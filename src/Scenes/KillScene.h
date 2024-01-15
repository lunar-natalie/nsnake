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
        explicit KillScene(GraphicsContext &context)
            : Scene(context, SceneID::KILL, static_cast<SceneFlags_t>(SceneFlags::SUBWIN)) {
            auto dimensions = V2i(m_context.extent / 2);
            auto offset = V2i(dimensions / 2);
            m_overlay = subwin(stdscr, dimensions.y, dimensions.x, offset.y, offset.x);
            setWindow(m_context, m_overlay, dimensions);
        }

        void update() override {
            putStrCenter("GAME OVER", m_context, -2);
            putStrCenter("Press RETURN to play again", m_context);
            wrefresh(m_overlay);
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