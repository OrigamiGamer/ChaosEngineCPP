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
        if (new_scene != nullptr) {
            new_scene->engine.refer(this->engine);
            this->_scenes.push_back(new_scene);
        }
    }

    void Stage::registerScene(Scene& new_scene)
    {
        this->registerScene(&new_scene);
    }

    void Stage::registerScene(Chaos::shared_ptr<Scene>& new_scene)
    {
        this->registerScene(new_scene.operator->());
    }

    void Stage::update()
    {
        for (auto& scene : this->_scenes) {
            scene->update();
        }
    }

    inline bool Stage::switchScene(std::string new_sceneName)
    {
        for (auto& _scene : this->_scenes) {
            if (_scene->GET_TOP_TYPE() == new_sceneName) {
                this->_preparedScene = _scene;
                return true;
            }
        }
        return false;
    }

    inline void Stage::switchScene(Scene* new_scene)
    {
        if (new_scene != nullptr) this->_preparedScene = new_scene;
    }

    inline void Stage::switchScene(Scene& new_scene)
    {
        this->switchScene(&new_scene);
    }

    inline void Stage::switchScene(Chaos::shared_ptr<Scene>& new_scene)
    {
        this->switchScene(new_scene.operator->());
    }

}