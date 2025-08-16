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



    void Scene::RegisterActor(GameObject::Actor* new_actor)
    {
        if (!new_actor) return;

        for (auto& actor : this->actors) {
            if (new_actor == actor) return; // the new actor has already been within this scene
        }

        new_actor->scene = this;
        this->actors.push_back(new_actor);
    }



}