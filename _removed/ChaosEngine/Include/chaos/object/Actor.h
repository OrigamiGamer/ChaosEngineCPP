#pragma once

#include "chaos/object/object.h"


namespace chaos::object {


    class Actor : public Base {
    private:
        Actor* _parentActor = nullptr;
        std::vector<Actor*> _childActors;

    public:
        device::Scene* scene = nullptr;
        vec2<float> position = { 0.0f,0.0f };
        vec2<float> size = { 0.0f,0.0f };
        vec2<float> pivot = { 0.0f,0.0f };
        float rotation = 0.0f;
        vec2<float> scale = { 1.0f,1.0f };
        float generalScale = 1.0f;

        Actor();

        virtual void onMessage(device::ActorMessage& message);

        bool attachToActor(Actor* in_parentActor);

        bool attachToActor(std::string parentActorName);

        void detachFromActor();

        inline Actor* getParentActor();

        inline std::vector<Actor*> getChildActors();

        Actor* getChildActor(std::string childActorName);

    };


}