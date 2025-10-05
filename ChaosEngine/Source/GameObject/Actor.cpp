#pragma once

#include "Class/GameObject/GameObject.h"

namespace Chaos::GameObject {



    Actor::Actor()
    {
        this->INIT("Actor");

    }



    Actor::~Actor()
    {

    }



    void Actor::onMessage(std::string* message)
    {

    }



    bool Actor::attachToActor(Actor* new_parentActor)
    {
        if (!new_parentActor) return false;
        if (!new_parentActor->scene) return false;

        if (new_parentActor->scene != this->scene) return false;  // the new parent and this actor are NOT within the same scene

        if (this->_parentActor) this->detachFromActor();
        new_parentActor->_childActors.push_back(this);
        this->_parentActor = new_parentActor;
        return true;
    }



    bool Actor::attachToActor(std::string parentActorName)
    {
        if (parentActorName.empty()) return false;
        if (!this->scene) return false;

        for (auto& actor : this->scene->actors) {
            if (actor->name == parentActorName) return this->attachToActor(actor);
        }
        return false;   // the new parent actor with this name does NOT exist in the scene of this actor
    }



    void Actor::detachFromActor()
    {
        for (auto it = this->_parentActor->_childActors.begin();it != this->_parentActor->_childActors.end();it++) {
            // remove this child actor from parent
            if ((*it) == this) this->_parentActor->_childActors.erase(it);
        }
        this->_parentActor = nullptr;
    }



    inline Actor* Actor::getParentActor()
    {
        return this->_parentActor;
    }



    inline std::vector<Actor*> Actor::getChildActors()
    {
        return this->_childActors;
    }



    Actor* Actor::getChildActor(std::string childActorName)
    {
        if (childActorName.empty()) return nullptr;

        for (auto& childActor : this->_childActors) {
            if (childActor->name == childActorName) return childActor;
        }
        return nullptr; // could NOT find the child actor with this name attached to this actor
    }



}