// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include <curses.h>

#include "App/Context.h"
#include "App/Scene.h"
#include "Scenes/GameScene.h"
#include "Scenes/KillScene.h"
#include "Scenes/MenuScene.h"
#include "Utils/Window.h"

namespace nsnake {
    // Map of scene IDs to functions each returning a new scene instance
    using SceneMap = std::unordered_map<SceneID, std::function<std::unique_ptr<Scene>(const DrawingContext &context)>>;

    class Application {
        const static SceneMap sceneMap;
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
                if (m_scene->hasFlag(SceneFlags::SUBWIN))
                    touchwin(stdscr);
                m_scene->update();

                // Draw default window border
                border(0, 0, 0, 0, 0, 0, 0, 0);

                // Process events
                auto ch = getch();// Get input and refresh
                switch (ch) {
                    case KEY_RESIZE:
                        updateContext();// Refresh limiting parameters for scene geometry
                        if (m_scene->hasFlag(SceneFlags::REDRAW))
                            erase();// Clear screen before next iteration
                        break;

                    case 'q':// Exit
                        done = true;
                        break;

                    default:
                        // Delegate the event to the current scene
                        auto newID = m_scene->processEvent(ch);
                        if (newID == m_scene->getID()) {
                            break;// Same scene: continue
                        } else if (newID == SceneID::NONE) {
                            done = true;// Null scene: exit
                        } else {
                            m_scene = sceneMap.at(newID)(m_drawingContext);// Next scene
                            if (m_scene == nullptr)
                                throw std::runtime_error("Invalid scene");
                            if (m_scene->hasFlag(SceneFlags::REDRAW))
                                erase();
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

    const SceneMap Application::sceneMap = {
            {SceneID::NONE, [](auto &c) { return nullptr; }},
            {SceneID::MENU, [](auto &c) { return std::make_unique<MenuScene>(c); }},
            {SceneID::GAME, [](auto &c) { return std::make_unique<GameScene>(c); }},
            {SceneID::KILL, [](auto &c) { return std::make_unique<KillScene>(c); }}};
}// namespace nsnake
