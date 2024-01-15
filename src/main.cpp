// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include <clocale>
#include <iostream>
#include <stdexcept>

#include <argparse/argparse.hpp>

#include "Application.h"

using namespace nsnake;

int main(int argc, char *argv[]) {
    // Assume ISO-8859-1 character set for curses
    setlocale(LC_ALL, "");

    // Parse arguments
    argparse::ArgumentParser program("nSnake");
    program.add_argument("--no-menu")
            .help("skips the menu scene")
            .default_value(false)
            .implicit_value(true);
    try {
        program.parse_args(argc, argv);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    SceneID initialScene = program["--no-menu"] == true ? SceneID::GAME : SceneID::MENU;
    try {
        // Create the application
        Application app(initialScene);
        // Initialize curses and start the main event loop
        app.start();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
