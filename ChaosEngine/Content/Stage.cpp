#pragma once

#include "Common.h"

namespace Chaos::Content {
    Stage::Stage(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("Stage");
    }

    Stage::~Stage()
    {

    }

    void Stage::registerScene(Scene* new_scene)
    {
        if (!new_scene) return;
        for (auto& _scene : this->_scenes) {
            if (_scene.get()->name == new_scene->name) return;  // scene already registered
        }
        new_scene->engine.refer(this->engine);
        this->_scenes.push_back(new_scene);
    }

    void Stage::registerScene(Scene& new_scene)
    {
        this->registerScene(&new_scene);
    }

    void Stage::registerScene(Chaos::shared_ptr<Scene>& new_scene)
    {
        this->registerScene(new_scene.get());
    }

    void Stage::update()
    {
        // update current scene
        if (this->_currentScene.has_value()) this->_currentScene->update();
        // update prepared scene
        if (this->_preparedScene.has_value()) {
            this->_preparedScene->update();
            if (this->_currentScene.has_value() ? this->_currentScene->onExit() : true) {
                this->_preparedScene->onEnter();
                this->_currentScene = this->_preparedScene;
                this->_preparedScene = nullptr;
            }
        }
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

    inline void Stage::switchScene(Chaos::shared_ptr<Scene>& new_scene)
    {
        this->switchScene(new_scene.get());
    }

}