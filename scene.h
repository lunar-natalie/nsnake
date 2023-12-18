//
// Created by Natalie Wiggins on 17/12/2023.
//

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

Scene * new_scene(SceneData const * data, SceneId id);

} // nsnake

#endif //NSNAKE_SCENE_H
