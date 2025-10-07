#pragma once

#include "Class/GameObject/GameObject.h"



namespace Chaos::GameObject {



    class Actor : public Base {
    private:
        Actor* _parentActor = nullptr;
        std::vector<Actor*> _childActors;

    public:
        InternalDevice::Scene* scene = nullptr;
        vec2<float> pos = { 0.0f,0.0f };
        vec2<float> size = { 0.0f,0.0f };
        vec2<float> pivot = { 0.0f,0.0f };
        float rotation = 0.0f;
        vec2<float> scale = { 1.0f,1.0f };
        float generalScale = 1.0f;

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
