// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_APP_SCENE_H
#define NSNAKE_APP_SCENE_H

#include "app/context.h"

namespace nsnake {

enum SceneID { NONE,
               MENU,
               GAME };

class Scene {
protected:
    const ApplicationContext& context;

public:
    const SceneID id;

    explicit Scene(ApplicationContext const& context, SceneID id)
        : context{context}, id{id}
    {}

    virtual ~Scene() = default;

    virtual void draw() = 0;
    virtual SceneID process_event(int ch) = 0;
};

}// namespace nsnake

#endif //NSNAKE_APP_SCENE_H
