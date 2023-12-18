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
    if (scene == nullptr)
        throw std::runtime_error("Failed to create initial scene");
    update_scene_data();
}

void Application::start()
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
                update_scene_data(); // Refresh limiting parameters for scene geometry
                erase(); // Redraw before next iteration
                break;

            case 'q': // Exit
                done = true;
                break;

            default:
                // Delegate the event to the current scene
                auto new_id = scene->process_event(ch);
                if (new_id == SceneId::NONE) {
                    // Exit if null scene returned
                    done = true;
                }
                else if (new_id != scene->id) {
                    // Clear graphics drawn by the current scene and create the new scene from the returned ID
                    erase();
                    scene = new_scene(&scene_data, new_id);
                    if (scene == nullptr)
                        throw std::runtime_error("Invalid scene");
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