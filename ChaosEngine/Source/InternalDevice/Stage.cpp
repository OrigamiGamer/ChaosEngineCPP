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

        std::cout << "[CALL] Stage -> release()" << std::endl;

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
        for (size_t i = 0;i < this->windows.size();i++) {
            auto& window = windows.at(i);

            if (window->getTitle() == windowTitle) {

                if (windowName != "" && window->name != windowName) continue;

                windows.erase(this->windows.begin() + i);
                i--;
            }
        }
    }



    void Stage::registerScene(Scene* new_scene)
    {
        if (!new_scene) return;
        for (auto& _scene : this->_scenes) {
            if (_scene) if (_scene->name == new_scene->name) return;  // scene already registered
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

            // handle window message
            if (!glfwWindowShouldClose(_glfwWindow)) {
                glfwSwapBuffers(_glfwWindow);
                glfwPollEvents();
            }
            else {
                // game exit
                if (this->engine->engineStartupProp.onGameExit ? this->engine->engineStartupProp.onGameExit() : true) {
                    // user confirmed
                    this->engine->stop();
                }
                // user denied
                glfwSetWindowShouldClose(_glfwWindow, false);
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
            if (_scene->name == new_sceneName) {
                this->_preparedScene = _scene;
                std::cout << "Stage -> switch to scene: " << new_sceneName.c_str() << std::endl;
                return true;
            }
        }
        return false;
    }



    inline void Stage::switchScene(Scene* new_scene)
    {
        if (!new_scene) return;
        this->switchScene(new_scene->name);
    }



    inline void Stage::switchScene(Scene& new_scene)
    {
        this->switchScene(&new_scene);
    }



}
