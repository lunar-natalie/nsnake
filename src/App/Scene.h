// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "App/Context.h"

namespace nsnake {
    enum SceneID {
        NONE,
        MENU,
        GAME
    };

    class Scene {
    protected:
        const SceneID m_id;
        const DrawingContext &m_context;

    public:
        explicit Scene(const DrawingContext &context, SceneID id)
            : m_context{context},
              m_id{id} {
        }

        virtual ~Scene() = default;

        virtual void update() = 0;
        virtual SceneID processEvent(int ch) = 0;

        [[nodiscard]] auto getID() const {
            return m_id;
        }
    };
}// namespace nsnake
