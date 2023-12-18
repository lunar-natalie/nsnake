//
// Created by Natalie Wiggins on 18/12/2023.
//

#ifndef NSNAKE_GAME_H
#define NSNAKE_GAME_H

#include "scene.h"

namespace nsnake {

class GameScene : public Scene {
public:
    explicit GameScene(SceneData const * data)
            : Scene(data)
    {}

    void draw() override;

    SceneId process_event(int ch) override;

    const SceneId id = SceneId::GAME;
};

} // nsnake

#endif //NSNAKE_GAME_H
