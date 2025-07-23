#pragma once

#include "InternalDevice/InternalDevice.h"

namespace Chaos::InternalDevice {



    Stage::Stage(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("Stage");
    }



    void Stage::registerScene(Scene* new_scene)
    {
        if (!new_scene) return;
        for (auto& _scene : this->_scenes) {
            if (_scene) if (_scene->name == new_scene->name) return;  // scene already registered
        }
        new_scene->engine = this->engine;
        this->_scenes.push_back(new_scene);
    }



    inline void Stage::registerScene(Scene& new_scene)
    {
        this->registerScene(&new_scene);
    }



    void Stage::update()
    {
        if (!this->engine) return;
        if (!this->engine->renderer) return;
        this->engine->renderer->beginDraw();
        // update current scene
        if (this->_currentScene) this->_currentScene->update();
        // update prepared scene
        if (this->_preparedScene) {
            this->_preparedScene->update();
            if (this->_currentScene ? this->_currentScene->onExiting() : true) {
                this->_preparedScene->onEntering();
                this->_currentScene = this->_preparedScene;
                this->_preparedScene = nullptr;
            }
        }
        this->engine->renderer->endDraw();
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
