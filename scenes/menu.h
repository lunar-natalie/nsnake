// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_SCENES_MENU_H
#define NSNAKE_SCENES_MENU_H

#include "scene.h"
#include "utils.h"

namespace nsnake {

class MenuScene : public Scene {
public:
    explicit MenuScene(ApplicationContext const& context)
        : Scene(context)
    {}

    void draw() override
    {
        addstr_center("Press RETURN to begin", context);
    }

    SceneID process_event(int ch) override
    {
        if (ch == '\r') {
            return SceneID::GAME;
        }
        return id;
    }

    const SceneID id = SceneID::MENU;
};

}// namespace nsnake

#endif//NSNAKE_SCENES_MENU_H
