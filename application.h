// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_APPLICATION_H
#define NSNAKE_APPLICATION_H

#include "scene.h"

namespace nsnake {

class Application {
public:
    Application();
    ~Application();

    void start();

private:
    Scene * scene;
    SceneData scene_data;

    void update_scene_data();
};

} // nsnake

#endif //NSNAKE_APPLICATION_H
