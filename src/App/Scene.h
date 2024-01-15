// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "App/Context.h"

namespace nsnake {
    enum class SceneID {
        NONE,
        MENU,
        GAME,
        KILL
    };

    enum SceneFlags : unsigned {
        NONE [[maybe_unused]],
        REDRAW,
        SUBWIN
    };

    class Scene {
    protected:
        const SceneID m_id;
        const GraphicsContext &m_context;
        const unsigned m_flags;

    public:
        explicit Scene(const GraphicsContext &context, SceneID id, unsigned flags = SceneFlags::REDRAW)
            : m_context{context},
              m_id{id},
              m_flags{flags} {}

        virtual ~Scene() = default;

        virtual void update() = 0;
        virtual SceneID processEvent(int ch) = 0;

        [[nodiscard]] auto getID() const { return m_id; }

        [[nodiscard]] constexpr bool hasFlag(SceneFlags f) const {
            return (m_flags & f) == 1;
        }
    };
}// namespace nsnake
