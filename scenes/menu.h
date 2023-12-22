// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_SCENES_MENU_H
#define NSNAKE_SCENES_MENU_H

#include "app/scene.h"
#include "utils/io.h"

namespace nsnake {

class MenuScene : public Scene {
public:
    explicit MenuScene(ApplicationContext const& context)
        : Scene(context, SceneID::MENU)
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
};

}// namespace nsnake

#endif//NSNAKE_SCENES_MENU_H
