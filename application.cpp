//
// Created by Natalie Wiggins on 16/12/2023.
//

#include <stdexcept>

#include <curses.h>

#include "application.h"
#include "menu.h"

namespace nsnake {

Application::Application()
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
    timeout(0); // Disable blocking on input

    // Initial scene
    scene = dynamic_cast<Scene *>(new MenuScene(&scene_data));
    update_scene_data();
}

void Application::start()
{
    auto done = false;
    do {
        // Default window border
        border(0, 0, 0, 0, 0, 0, 0, 0);

        // Draw current scene
        if (scene != nullptr)
            scene->draw();

        // Process events
        auto ch = getch(); // Get input and refresh
        switch (ch) {
            case KEY_RESIZE:
                update_scene_data();
                // Redraw
                erase();
                break;

            case 'q':
                // Exit
                done = true;
                break;

            default:
                if (scene != nullptr) {
                    // Delegate event to the current scene
                    auto new_id = scene->process_event(ch);
                    if (new_id == SceneId::NONE)
                        done = true;  // Exit if null scene returned
                    else if (new_id != scene->id)
                        scene = new_scene(&scene_data, new_id); // Create new scene from return ID
                }
                break;
        }
    } while (!done);
}

void Application::update_scene_data()
{
    scene_data.window_extent = get_extent(stdscr);
}

Application::~Application()
{
    // Clear screen
    erase();
    refresh();

    // De-initialize curses
    endwin();
}

} // nsnake