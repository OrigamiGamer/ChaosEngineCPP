#pragma once

#include "Class/InternalDevice/InternalDevice.h"

namespace Chaos::InternalDevice {



    Stage::Stage()
    {
        this->INIT("Stage");
    }



    void Stage::release()
    {
        for (auto& scene : this->_scenes) {
            scene->release();
        }

        for (auto& window : this->windows) {
            window->release();
        }

        Log::OutputStream _out("INFO");
        _out.push("Stage -> release()");
        this->_logger.print(_out);

    }



    void Stage::registerWindow(WindowX::Window* new_window)
    {
        new_window->stage = this;
        this->windows.push_back(new_window);
    }



    void Stage::registerWindow(WindowX::Window& new_window)
    {
        this->registerWindow(&new_window);
    }



    void Stage::unregisterWindow(std::string windowTitle, std::string windowName)
    {
        for (size_t i = 0; i < this->windows.size(); i++) {
            auto& window = windows.at(i);

            if (window->getTitle() != windowTitle) continue;
            if (windowName == "" || window->nameId != windowName) continue;

            windows.erase(this->windows.begin() + i);
            i--;
        }
    }



    void Stage::unregisterWindow(WindowX::Window* new_window)
    {
        for (size_t i = 0; i < this->windows.size(); i++) {
            if (this->windows.at(i) == new_window)
                this->windows.erase(this->windows.begin() + i);
        }
    }



    void Stage::unregisterWindow(WindowX::Window& new_window)
    {
        this->unregisterWindow(&new_window);
    }



    void Stage::registerScene(Scene* new_scene)
    {
        if (!new_scene) return;
        for (auto& _scene : this->_scenes) {
            if (_scene) if (_scene->nameId == new_scene->nameId) return;  // scene already registered
        }
        new_scene->stage = this;
        this->_scenes.push_back(new_scene);
    }



    inline void Stage::registerScene(Scene& new_scene)
    {
        this->registerScene(&new_scene);
    }



    void Stage::_updateWindow()
    {
        for (auto& window : this->windows) {
            auto& _glfwWindow = window->_glfwWindow;

            // Window Close
            if (glfwWindowShouldClose(_glfwWindow)) {
                // request to close window
                if (window->startupProperty.onWindowClose ? window->startupProperty.onWindowClose() : true) {
                    // user accpeted
                    window->release();
                    unregisterWindow(window);
                }
                else {
                    // user rejected
                    glfwSetWindowShouldClose(_glfwWindow, false);
                }
            }
            else {
                // Window Update
                glfwSwapBuffers(_glfwWindow);                              // optional [?]
                glfwPollEvents();   // handle window messages
            }
        }

        if (this->windows.empty()) {
            // Game Exit
            if (this->engine->engineStartupProp.onGameExit ? this->engine->engineStartupProp.onGameExit() : true) {
                // user accpeted
                this->engine->stop();
            }
        }
    }



    void Stage::update()
    {
        // update current scene
        if (this->_currentScene) this->_currentScene->update();
        // update prepared scene
        if (this->_preparedScene) {
            this->_preparedScene->update();
            if (this->_currentScene ? this->_currentScene->onExiting() : true) {
                this->_preparedScene->onEntered();
                this->_currentScene = this->_preparedScene;
                this->_preparedScene = nullptr;
            }
        }
        if (!this->engine) return;
        if (!this->engine->renderer) return;
        this->engine->renderer->_render();
    }



    inline bool Stage::switchScene(std::string new_sceneName)
    {
        for (auto& _scene : this->_scenes) {
            if (_scene->nameId == new_sceneName) {
                this->_preparedScene = _scene;

                Log::OutputStream _out("WARN");
                _out.push("Stage -> entered scene -> \"")->push(new_sceneName)->push("\"");
                this->_logger.print(_out);

                return true;
            }
        }
        return false;
    }



    inline void Stage::switchScene(Scene* new_scene)
    {
        if (!new_scene) return;
        this->switchScene(new_scene->nameId);
    }



    inline void Stage::switchScene(Scene& new_scene)
    {
        this->switchScene(&new_scene);
    }



}
