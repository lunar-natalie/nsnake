// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "App/Scene.h"
#include "Utils/IO.h"

namespace nsnake {
    class MenuScene : public Scene {
    public:
        explicit MenuScene(const DrawingContext &context) : Scene(context, SceneID::MENU) {}

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
