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
    ApplicationContext context;
    Scene * scene;

    void update_context();
};

}// namespace nsnake

#endif //NSNAKE_APPLICATION_H
