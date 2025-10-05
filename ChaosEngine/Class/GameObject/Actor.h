#pragma once

#include "Class/GameObject/GameObject.h"



namespace Chaos::GameObject {



    class Actor : public Base {
    private:
        Actor* _parentActor = nullptr;
        std::vector<Actor*> _childActors;

    public:
        InternalDevice::Scene* scene = nullptr;
        // vec2<float> pos;


        Actor();

        ~Actor();

        virtual void onMessage(InternalDevice::ActorMessage& message);

        bool attachToActor(Actor* new_parentActor);

        bool attachToActor(std::string parentActorName);

        void detachFromActor();

        inline Actor* getParentActor();

        inline std::vector<Actor*> getChildActors();

        Actor* getChildActor(std::string childActorName);

    };



}
