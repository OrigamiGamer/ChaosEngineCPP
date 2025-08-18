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
        for (auto& actor : this->actors) {

        }
    }



    void Scene::onEntered()
    {

    }



    bool Scene::onExiting()
    {
        return true;
    }



    void Scene::onHotkeyPressed(int virtualKey)
    {

    }



    void Scene::onHotkeyPressed(std::string hotkeyName)
    {

    }



    void Scene::onHotkeyReleased(int virtualKey)
    {

    }



    void Scene::onHotkeyReleased(std::string hotkeyName)
    {

    }



    void Scene::registerActor(GameObject::Actor* new_actor)
    {
        if (!new_actor) return;

        for (auto& actor : this->actors) {
            if (new_actor == actor) return; // the new actor has already been within this scene
        }

        new_actor->scene = this;
        this->actors.push_back(new_actor);
    }



    bool Scene::sendMessage(std::string actorType, std::string actorName, std::string message)
    {
        if (actorType.empty() || actorType == "" || actorName.empty() || actorName == "") return false;

        for (auto& _actor : this->actors) {
            if (_actor->GET_TOP_TYPE() == actorType && _actor->name == actorName) {
                _actor->onMessage(message); // NOTICE: the string type of message will be upgraded into Message type
                return true;
            }
        }
        return false;
    }



    bool Scene::sendMessage(GameObject::Actor* actor, std::string message)
    {
        if (!actor) return false;

        actor->onMessage(message);  // NOTICE: the string type of message will be upgraded into Message type
        return true;
    }



}