// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_SCENES_MENU_H
#define NSNAKE_SCENES_MENU_H

#include "scene.h"

namespace nsnake {

class MenuScene : public Scene {
public:
    explicit MenuScene(ApplicationContext const& context);

    void draw() override;
    SceneId process_event(int ch) override;

    const SceneId id = SceneId::MENU;
};

}// namespace nsnake

#endif//NSNAKE_SCENES_MENU_H
