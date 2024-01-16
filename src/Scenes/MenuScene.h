// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <stdexcept>

#include "App/Scene.h"
#include "Utils/IO.h"

namespace nsnake {
    class MenuScene : public Scene {
        static const int LINE_COUNT = 1;

    public:
        explicit MenuScene(Context &ctx) : Scene(ctx, SceneID::MENU) {
            if (m_context.extent.y < LINE_COUNT)
                throw std::runtime_error("Invalid window size");
        }

        void update() override {
            putStrCenter("Press RETURN to begin", m_context);
        }

        SceneID processEvent(int ch) override {
            if (ch == '\r')
                return SceneID::GAME;
            return m_id;
        }
    };
}// namespace nsnake
