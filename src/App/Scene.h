// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <type_traits>

#include "App/Context.h"
#include "Utils/Window.h"

namespace nsnake {
    enum class SceneID {
        NONE,
        MENU,
        GAME,
        KILL
    };

    enum class SceneFlags : unsigned {
        NONE = 0,
        SUBWIN = 1 << 0
    };

    using SceneFlags_t = std::underlying_type<SceneFlags>::type;

    inline constexpr SceneFlags_t operator|(const SceneFlags &lhs, const SceneFlags &rhs) {
        return static_cast<SceneFlags_t>(lhs) | static_cast<SceneFlags_t>(rhs);
    }
    inline constexpr SceneFlags_t operator&(const SceneFlags_t &lhs, const SceneFlags &rhs) {
        return lhs & static_cast<SceneFlags_t>(rhs);
    }
    inline constexpr bool operator==(const SceneFlags_t &lhs, const SceneFlags &rhs) {
        return lhs == static_cast<SceneFlags_t>(rhs);
    }

    class Scene {
    protected:
        const SceneID m_id;
        const SceneFlags_t m_flags;
        GraphicsContext &m_context;

    public:
        explicit Scene(GraphicsContext &context, SceneID id, SceneFlags_t flags = static_cast<SceneFlags_t>(SceneFlags::NONE))
            : m_context{context},
              m_id{id},
              m_flags{flags} {}

        virtual ~Scene() = default;

        virtual void update() = 0;
        virtual SceneID processEvent(int ch) = 0;

        [[nodiscard]] auto getID() const { return m_id; }

        [[nodiscard]] constexpr bool hasFlag(SceneFlags f) const {
            return (m_flags & f) == f;
        }
    };
}// namespace nsnake
