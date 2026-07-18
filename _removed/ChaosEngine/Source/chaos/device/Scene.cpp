#include "chaos/device/device.h"

namespace chaos::device {



    Scene::Scene(std::string in_sceneName)
    {
        this->INIT("Scene");
        this->SET_NAME(in_sceneName);

    }



    void Scene::release()
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



    void Scene::onHotkeyPressed(int keycode)
    {

    }



    void Scene::onHotkeyPressed(std::string hotkeyName)
    {

    }



    void Scene::onHotkeyReleased(int keycode)
    {

    }



    void Scene::onHotkeyReleased(std::string hotkeyName)
    {

    }



    void Scene::registerActor(object::Actor* in_actor)
    {
        if (!in_actor) return;

        for (auto& actor : this->actors) {
            if (in_actor == actor) return; // the new actor has already been within this scene
        }

        in_actor->scene = this;
        this->actors.push_back(in_actor);
    }



    bool Scene::dispatchMessage(ActorMessage& message)
    {
        if (message.actorType.empty()) return false;

        this->actorMessages.push_back(message);

        for (auto& actor : this->actors) {
            if (actor->GET_TOP_TYPE() == message.actorType && actor->nameId == message.actorName) {
                actor->onMessage(this->actorMessages.back());
                message.isReceived = true;
                return true;
            }
        }

        return false;
    }



}