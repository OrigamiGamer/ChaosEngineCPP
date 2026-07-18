#pragma once

#include "chaos/device/device.h"


namespace chaos::device {



    class Engine : public Base {
    private:
        void windowUpdate();

        void engineUpdate();

    public:
        graphics::Renderer* renderer = nullptr;
        device::Stage* stage = nullptr;
        physics::PhysicsEngine* physicsEngine = nullptr;

        device::EngineStartupProperty engineStartupProp;
        bool gameRunningState = false;
        /** units: microseconds */
        unsigned long long lastEngineTime = 0;
        /** units: microseconds */
        unsigned long long deltaEngineTime = 0;

        Engine();

        bool initialize();

        void start(EngineStartupProperty* in_engineStartupProp = nullptr);

        void start(
            unsigned int in_fps = 60,
            Callback_GameInit in_onGameInit = nullptr,
            Callback_GameExit in_onGameExit = nullptr
        );

        void stop();

        void release();

        void registerRenderer(graphics::Renderer* in_renderer);

        void registerStage(device::Stage* in_stage);

        void registerPhysicsEngine(physics::PhysicsEngine* in_PhysicsEngine);

    };



}