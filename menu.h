//
// Created by Natalie Wiggins on 17/12/2023.
//

#ifndef NSNAKE_MENU_H
#define NSNAKE_MENU_H

#include "scene.h"

namespace nsnake {

class MenuScene : public Scene {
public:
    explicit MenuScene(SceneData const * data)
            : Scene(data)
    {}

    void draw() override;
    SceneId process_event(int ch) override;

    const SceneId id = SceneId::MENU;
};

} // nsnake

#endif //NSNAKE_MENU_H
