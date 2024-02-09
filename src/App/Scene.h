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
        NONE [[maybe_unused]] = 0,
        SUBWIN = 1 << 1,
        BORDER = 1 << 2,
        REDRAW = 1 << 3,
        RESIZE = 1 << 4,
    };

    using SceneFlags_t = std::underlying_type<SceneFlags>::type;
    inline constexpr SceneFlags_t operator|(const SceneFlags & lhs, const SceneFlags & rhs)
    {
        return static_cast<SceneFlags_t>(lhs) | static_cast<SceneFlags_t>(rhs);
    }
    inline constexpr SceneFlags_t operator|(const SceneFlags_t & lhs, const SceneFlags & rhs)
    {
        return lhs | static_cast<SceneFlags_t>(rhs);
    }
    inline constexpr SceneFlags_t operator&(const SceneFlags_t & lhs, const SceneFlags & rhs)
    {
        return lhs & static_cast<SceneFlags_t>(rhs);
    }
    inline constexpr bool operator==(const SceneFlags_t & lhs, const SceneFlags & rhs)
    {
        return lhs == static_cast<SceneFlags_t>(rhs);
    }

    class Scene {
    protected:
        const SceneID m_id;
        const SceneFlags_t m_flags;
        Context & m_context;

    public:
        explicit Scene(Context & ctx, SceneID id, SceneFlags_t flags = SceneFlags::BORDER | SceneFlags::REDRAW | SceneFlags::RESIZE)
            : m_context{ctx}, m_id{id}, m_flags{flags}
        {
            if (!hasFlag(SceneFlags::SUBWIN))
                setWindow(m_context, stdscr);
        }

        virtual ~Scene() = default;

        virtual void update() = 0;
        virtual SceneID processEvent(int ch) = 0;

        [[nodiscard]] constexpr auto getID() const { return m_id; }

        [[nodiscard]] constexpr bool hasFlag(SceneFlags f) const
        {
            return (m_flags & f) == f;
        }
    };
}// namespace nsnake
