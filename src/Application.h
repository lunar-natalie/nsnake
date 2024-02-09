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
    using SceneMap = std::unordered_map<SceneID, std::function<std::unique_ptr<Scene>(Context &)>>;

    class Application {
        static const SceneMap sceneMap;
        Context m_context{};
        V2i m_screenExtent{};
        std::unique_ptr<Scene> m_scene;

    public:
        explicit Application(SceneID initialScene)
        {
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

            m_screenExtent = getExtent(stdscr);

            // Setup initial scene
            m_scene = sceneMap.at(initialScene)(m_context);
        }

        void start()
        {
            auto done = false;
            do {
                // Update screen data
                m_scene->update();
                if (m_scene->hasFlag(SceneFlags::BORDER))
                    wborder(m_context.window, 0, 0, 0, 0, 0, 0, 0, 0);
                if (m_scene->hasFlag(SceneFlags::SUBWIN))
                    touchwin(stdscr);

                // Get input and refresh
                auto ch = getch();
                if (m_context.window != stdscr)
                    wrefresh(m_context.window);
                // Process events
                switch (ch) {
                    case KEY_RESIZE:
                        if (m_scene->hasFlag(SceneFlags::REDRAW))
                            erase();
                        werase(m_context.window);
                        if (m_scene->hasFlag(SceneFlags::RESIZE))
                            updateExtents();
                        break;
                    case 'q':
                        // Exit
                        done = true;
                        break;
                    default:
                        // Delegate the event to the current scene
                        auto newID = m_scene->processEvent(ch);
                        if (newID == m_scene->getID()) {
                            // Same scene, continue
                            break;
                        } else if (newID == SceneID::NONE) {
                            // Null scene, exit
                            done = true;
                        } else {
                            // Next scene
                            m_scene = sceneMap.at(newID)(m_context);
                            if (m_scene == nullptr)
                                throw std::runtime_error("Invalid scene");
                            if (m_scene->hasFlag(SceneFlags::REDRAW))
                                erase();
                            werase(m_context.window);
                        }
                        break;
                }
            } while (!done);
        }

        ~Application()
        {
            // Clear screen and de-initialize curses
            erase();
            refresh();
            endwin();
        }

    private:
        void updateExtents()
        {
            auto & oldExtent = m_screenExtent;
            auto newExtent = getExtent(stdscr);
            m_context.extent += newExtent - oldExtent;
            oldExtent = newExtent;
        }
    };

    const SceneMap Application::sceneMap = {
            {SceneID::NONE, [](auto & ctx) { return nullptr; }},
            {SceneID::MENU, [](auto & ctx) { return std::make_unique<MenuScene>(ctx); }},
            {SceneID::GAME, [](auto & ctx) { return std::make_unique<GameScene>(ctx); }},
            {SceneID::KILL, [](auto & ctx) { return std::make_unique<KillScene>(ctx); }}};
}// namespace nsnake
