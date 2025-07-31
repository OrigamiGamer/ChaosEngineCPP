#pragma once

#include "InternalDevice/InternalDevice.h"

namespace Chaos::InternalDevice {



    Scene::Scene(std::string new_sceneName)
    {
        this->INIT("Scene");
        this->SET_NAME(new_sceneName);

    }



    void release()
    {

    }



    void Scene::update()
    {

    }



    void Scene::onEntered()
    {

    }



    bool Scene::onExiting()
    {
        return true;
    }



}