// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_APPLICATION_H
#define NSNAKE_APPLICATION_H

#include <memory>
#include <stdexcept>

#include <curses.h>

#include "app/context.h"
#include "app/scene.h"
#include "app/scene_map.h"
#include "scenes/menu.h"
#include "utils/window.h"

namespace nsnake {

class Application {
    ApplicationContext context;
    std::unique_ptr<Scene> scene;

public:
    Application()
    {
        // Initialize curses
        if (initscr() == nullptr)
            throw std::runtime_error("Failed to initialize curses screen");

        cbreak(); // Disable line buffering
        noecho(); // Don't echo input to output
        curs_set(0); // Disable cursor

        nonl(); // Disable newline translation for faster cursor motion
        intrflush(stdscr, FALSE); // Disable flush on keyboard interrupt
        keypad(stdscr, TRUE); // Enable input
        nodelay(stdscr, TRUE); // Disable blocking on input

        // Setup initial scene
        scene = std::make_unique<MenuScene>(context);
        update_context();
    }

    void start()
    {
        auto done = false;
        do {
            // Draw
            border(0, 0, 0, 0, 0, 0, 0, 0); // Default window border
            scene->draw(); // Contents of current scene

            // Process events
            auto ch = getch(); // Get input and refresh
            switch (ch) {
                case KEY_RESIZE:
                    update_context(); // Refresh limiting parameters for scene geometry
                    erase(); // Redraw before next iteration
                    break;

                case 'q': // Exit
                    done = true;
                    break;

                default:
                    // Delegate the event to the current scene.
                    auto new_id = scene->process_event(ch);
                    if (new_id == scene->id) { // Same scene: continue
                        break;
                    }
                    else if (new_id == SceneID::NONE) { // Null scene: exit
                        done = true;
                    }
                    else {
                        // Clear graphics drawn by the current scene and create the new scene from the returned ID.
                        erase();
                        scene = scene_map.at(new_id)(context);
                        if (scene == nullptr)
                            throw std::runtime_error("Invalid scene");
                    }
                    break;
            }
        } while (!done);
    }

private:
    void update_context()
    {
        context.window_extent = get_extent(stdscr);
    }

public:
    ~Application()
    {
        // Clear screen
        erase();
        refresh();

        // De-initialize curses
        endwin();
    }
};

}// namespace nsnake

#endif //NSNAKE_APPLICATION_H
