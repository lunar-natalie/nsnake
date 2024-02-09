// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <stdexcept>

#include <curses.h>

#include <App/Scene.h>
#include <Utils/IO.h>

namespace nsnake {
    class KillScene : public Scene {
        static const int LINE_COUNT = 7;
        WINDOW * m_overlay;

    public:
        explicit KillScene(Context & ctx)
            : Scene(ctx, SceneID::KILL, SceneFlags::SUBWIN | SceneFlags::BORDER)
        {
            // Create centered overlay window
            V2i extent{.x = m_context.extent.x / 2, .y = LINE_COUNT};
            V2i offset = V2i(m_context.extent / 2) - V2i(extent / 2);
            if (auto win = subwin(stdscr, extent.y, extent.x, offset.y, offset.x); win != nullptr) {
                m_overlay = win;
            } else {
                throw std::runtime_error("Failed to create overlay window");
            }
            setWindow(m_context, m_overlay);
        }

        void update() override
        {
            putStrCenter("GAME OVER", m_context, -1);
            putStrCenter("Press RETURN to play again", m_context, 1);
            wrefresh(m_overlay);
        }

        SceneID processEvent(int ch) override
        {
            if (ch == '\r')
                return SceneID::GAME;
            return m_id;
        }

        ~KillScene() override
        {
            delwin(m_overlay);
        }
    };
}// namespace nsnake