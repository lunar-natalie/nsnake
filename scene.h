// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_SCENE_H
#define NSNAKE_SCENE_H

#include "geometry.h"

namespace nsnake {

enum class SceneId {
    NONE,
    MENU,
    GAME
};

struct SceneData {
    V2i window_extent = {0, 0};

    V2i window_center() const
    {
        return static_cast<V2i>(window_extent / 2);
    }
};

class Scene {
public:
    explicit Scene(SceneData const * data)
            : data{data}
    {}

    virtual ~Scene() = default;

    virtual void draw() = 0;
    virtual SceneId process_event(int ch) = 0;

    const SceneId id = SceneId::NONE;

protected:
    const SceneData * data;
};

Scene * new_scene(SceneId id, SceneData const * data) noexcept;

}// namespace nsnake

#endif //NSNAKE_SCENE_H
