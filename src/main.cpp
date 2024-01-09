// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include <clocale>
#include <iostream>
#include <stdexcept>

#include "Application.h"

using namespace nsnake;

int main(int argc, char *argv[]) try {
    // Assume ISO-8859-1 character set for curses
    setlocale(LC_ALL, "");

    // Parse arguments
    SceneID initialScene = SceneID::MENU;
    if (argc > 1) {
        if (std::string(argv[1]) == "--no-menu")
            initialScene = SceneID::GAME;
    }

    // Create the application
    Application app(initialScene);
    // Initialize curses and start the main event loop
    app.start();

    return 0;
} catch (std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
}
