#pragma once

#include "Common.h"

namespace Chaos::Content {
    Scene::Scene(std::string new_sceneName)
    {
        this->INIT("Scene");
        this->SET_NAME(new_sceneName);

    }

    Scene::~Scene()
    {

    }

    void Scene::update()
    {

    }

    void Scene::onEnter()
    {

    }

    bool Scene::onExit()
    {
        return true;
    }



}