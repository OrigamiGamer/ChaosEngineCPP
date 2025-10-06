#pragma once

#include "Class/InternalDevice/InternalDevice.h"

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



    bool Scene::dispatchMessage(ActorMessage& message)
    {
        if (message.actorType.empty()) return false;

        this->actorMessages.push_back(message);

        for (auto& actor : this->actors) {
            if (actor->GET_TOP_TYPE() == message.actorType && actor->name == message.actorName) {
                actor->onMessage(this->actorMessages.back());
                message.isReceived = true;
                return true;
            }
        }

        return false;
    }



}