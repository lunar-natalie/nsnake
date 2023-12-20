// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_SCENE_H
#define NSNAKE_SCENE_H

#include "context.h"
#include "geometry.h"

namespace nsnake {

enum class SceneId {
    NONE,
    MENU,
    GAME
};

class Scene {
public:
    explicit Scene(ApplicationContext const& context)
        : context{context}
    {}

    virtual ~Scene() = default;

    virtual void draw() = 0;
    virtual SceneId process_event(int ch) = 0;

    const SceneId id = SceneId::NONE;

protected:
    const ApplicationContext& context;
};

Scene* new_scene(SceneId id, ApplicationContext const& context);

}// namespace nsnake

#endif //NSNAKE_SCENE_H
