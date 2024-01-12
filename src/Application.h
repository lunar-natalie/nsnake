// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <memory>
#include <stdexcept>

#include <curses.h>

#include "App/Context.h"
#include "App/Scene.h"
#include "App/SceneMap.h"
#include "Scenes/Menu.h"
#include "Utils/Window.h"

namespace nsnake {
    class Application {
        ApplicationContext m_appContext;
        DrawingContext m_drawingContext;
        std::unique_ptr<Scene> m_scene;

    public:
        explicit Application(SceneID initialScene) {
            // Initialize curses
            if (initscr() == nullptr)
                throw std::runtime_error("Failed to initialize curses screen");

            cbreak();   // Disable line buffering
            noecho();   // Don't echo input to output
            curs_set(0);// Disable cursor

            nonl();                  // Disable newline translation for faster cursor motion
            intrflush(stdscr, FALSE);// Disable flush on keyboard interrupt
            keypad(stdscr, TRUE);    // Enable input
            nodelay(stdscr, TRUE);   // Disable blocking on input

            // Setup initial scene
            updateContext();
            m_scene = sceneMap.at(initialScene)(m_drawingContext);
        }

        void start() {
            auto done = false;
            do {
                m_scene->update();

                // Draw default window border
                border(0, 0, 0, 0, 0, 0, 0, 0);

                // Process events
                auto ch = getch();// Get input and refresh
                switch (ch) {
                    case KEY_RESIZE:
                        updateContext();// Refresh limiting parameters for scene geometry
                        erase();        // Redraw before next iteration
                        break;

                    case 'q':// Exit
                        done = true;
                        break;

                    default:
                        // Delegate the event to the current scene
                        auto newID = m_scene->processEvent(ch);
                        if (newID == m_scene->getID()) {
                            // Same scene: continue
                            break;
                        } else if (newID == SceneID::NONE) {
                            // Null scene: exit
                            done = true;
                        } else {
                            // Clear graphics drawn by the current scene and create the new scene from the returned ID
                            erase();
                            m_scene = sceneMap.at(newID)(m_drawingContext);
                            if (m_scene == nullptr)
                                throw std::runtime_error("Invalid scene");
                        }
                        break;
                }
            } while (!done);
        }

        ~Application() {
            // Clear screen
            erase();
            refresh();

            // De-initialize curses
            endwin();
        }

    private:
        void updateContext() {
            m_appContext.windowExtent = getExtent(stdscr);
            m_drawingContext = createDrawingContext();
        }

        [[nodiscard]] DrawingContext createDrawingContext() const {
            auto border = V2i::uniform(ApplicationContext::borderWidth);
            return {.extent = m_appContext.windowExtent - (2 * border), .offset = border};
        }
    };
}// namespace nsnake
