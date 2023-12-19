//
// Created by Natalie Wiggins on 16/12/2023.
//

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
