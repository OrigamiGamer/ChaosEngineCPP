#pragma once

#include "Class/InternalDevice/InternalDevice.h"



namespace Chaos::InternalDevice {



    class Engine : public Base {
    private:
        void windowUpdate();

        void engineUpdate();

    public:
        GraphicX::Renderer* renderer = nullptr;
        InternalDevice::Stage* stage = nullptr;
        PhysicX::PhysicsEngine* physicsEngine = nullptr;

        InternalDevice::EngineStartupProperty engineStartupProp;
        bool gameRunningState = false;
        unsigned long long lastEngineTime = 0;  // units: microseconds
        unsigned long long deltaEngineTime = 0; // units: microseconds

        Engine();

        bool initialize();

        void start(EngineStartupProperty* new_engineStartupProp = nullptr);

        void start(
            unsigned int new_fps = 60,
            Callback_GameInit new_onGameInit = nullptr,
            Callback_GameExit new_onGameExit = nullptr
        );

        void stop();

        void release();

        void registerRenderer(GraphicX::Renderer* new_renderer);

        void registerStage(InternalDevice::Stage* new_stage);

        void registerPhysicsEngine(PhysicX::PhysicsEngine* new_physicsEngine);

    };



}