// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include <clocale>
#include <iostream>
#include <stdexcept>
#include <string>

#include <argparse/argparse.hpp>

#include "Application.h"

using namespace nsnake;

const std::string programName = "nSnake";
const std::string versionInfo = programName + " " NSNAKE_VERSION "\n"
                                              "Copyright (c) 2024 Natalie Wiggins. All rights reserved.\n"
                                              "Provided under the terms of the BSD 3-Clause license.\n"
                                              "You should have received a copy of the license along with this program. If not, see <https://opensource.org/license/bsd-3-clause/>.";

int main(int argc, char *argv[]) {
    // Assume ISO-8859-1 character set for curses
    setlocale(LC_ALL, "");

    // Parse arguments
    argparse::ArgumentParser program(programName, versionInfo);
#ifndef NDEBUG
    program.add_argument("-n", "--no-menu")
            .help("skips the initial menu scene")
            .default_value(false)
            .implicit_value(true);
#endif//NDEBUG
    try {
        program.parse_args(argc, argv);
    } catch (std::exception &e) {// Invalid argument
        std::cerr << e.what() << std::endl;
        std::cerr << program;// Show usage
        return 1;
    }

    SceneID initialScene = SceneID::MENU;
#ifndef NDEBUG
    if (program["--no-menu"] == true)
        initialScene = SceneID::GAME;
#endif//NDEBUG

    try {
        // Create the application
        Application app(initialScene);
        // Initialize curses and start the main event loop
        app.start();
    } catch (std::runtime_error &e) {
#ifndef NDEBUG
        std::cerr << e.what() << std::endl;
#endif//NDEBUG
        return 1;
    }

    return 0;
}
