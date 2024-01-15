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
    using SceneMap = std::unordered_map<SceneID, std::function<std::unique_ptr<Scene>(GraphicsContext &context)>>;

    class Application {
        static const SceneMap sceneMap;
        ApplicationContext m_appContext;
        GraphicsContext m_gfxContext;
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

            // Initialize contexts
            m_appContext = {.windowExtent = getExtent(stdscr)};
            m_gfxContext = initGfxContext();

            // Setup initial scene
            m_scene = sceneMap.at(initialScene)(m_gfxContext);
        }

        void start() {
            auto done = false;
            do {
                if (m_scene->hasFlag(SceneFlags::SUBWIN))
                    touchwin(stdscr);

                // Draw default window border
                wborder(m_gfxContext.window, 0, 0, 0, 0, 0, 0, 0, 0);

                m_scene->update();

                // Process events
                auto ch = getch();// Get input and refresh
                switch (ch) {
                    case KEY_RESIZE:
                        updateContexts();
                        werase(m_gfxContext.window);
                        break;

                    case 'q':// Exit
                        done = true;
                        break;

                    default:// Delegate the event to the current scene
                        auto newID = m_scene->processEvent(ch);
                        if (newID == m_scene->getID()) {
                            // Same scene, continue
                            break;
                        } else if (newID == SceneID::NONE) {
                            // Null scene, exit
                            done = true;
                        } else {
                            // Next scene
                            m_gfxContext = initGfxContext();
                            m_scene = sceneMap.at(newID)(m_gfxContext);
                            if (m_scene == nullptr)
                                throw std::runtime_error("Invalid scene");
                            werase(m_gfxContext.window);
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
        [[nodiscard]] GraphicsContext initGfxContext() const {
            auto border = V2i::uniform(ApplicationContext::borderWidth);
            return {.window = stdscr, .extent = m_appContext.windowExtent - (2 * border), .offset = border};
        }

        void updateContexts() {
            auto &oldExtent = m_appContext.windowExtent;
            auto newExtent = getExtent(stdscr);
            m_gfxContext.extent += newExtent - oldExtent;
            oldExtent = newExtent;
        }
    };

    const SceneMap Application::sceneMap = {
            {SceneID::NONE, [](auto &c) { return nullptr; }},
            {SceneID::MENU, [](auto &c) { return std::make_unique<MenuScene>(c); }},
            {SceneID::GAME, [](auto &c) { return std::make_unique<GameScene>(c); }},
            {SceneID::KILL, [](auto &c) { return std::make_unique<KillScene>(c); }}};
}// namespace nsnake
