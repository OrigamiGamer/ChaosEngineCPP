#include "chaos/device/device.h"

namespace chaos::device {



    Engine::Engine()
    {
        this->INIT("Engine");

    }



    bool Engine::initialize()
    {
        // initialize GLFW
        if (!glfwInit()) return false;
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        this->gameRunningState = true;

        return true;
    }



    void Engine::start(EngineStartupProperty* in_engineStartupProp)
    {
        // store startup property of engine
        if (in_engineStartupProp) {
            // custom property
            this->engineStartupProp = *in_engineStartupProp;
        }
        else {
            // default property
            this->engineStartupProp.fps = 60;
            this->engineStartupProp.onGameInit = nullptr;
            this->engineStartupProp.onGameExit = []()-> bool {return true;};
        }


        // uniform chrono units: microseconds
        this->lastEngineTime = system::GetSystemTime();
        unsigned long long currentEngineTime = 0;

        // Game Init
        if (this->engineStartupProp.onGameInit) this->engineStartupProp.onGameInit();

        // Game Loop
        unsigned long long timeSlept = 0;
        while (this->gameRunningState) {

            // update window
            windowUpdate();

            // FPS Limit
            unsigned long long cycleTime = (1000 * 1000) / this->engineStartupProp.fps;
            timeSlept += this->deltaEngineTime;
            if (timeSlept >= cycleTime) {
                // update engine
                engineUpdate();
                timeSlept -= cycleTime;
                if (timeSlept < 0) timeSlept = 0;
            }

            // while one frame finished
            currentEngineTime = system::GetSystemTime();
            this->deltaEngineTime = currentEngineTime - lastEngineTime;
            lastEngineTime = currentEngineTime;

        }
    }



    void Engine::start(
        unsigned int fps,
        Callback_GameInit in_onGameInit,
        Callback_GameExit in_onGameExit
    )
    {
        EngineStartupProperty in_engineStartupProp;
        in_engineStartupProp.fps = fps;
        in_engineStartupProp.onGameInit = in_onGameInit;
        in_engineStartupProp.onGameExit = in_onGameExit;
        this->start(&in_engineStartupProp);
    }



    void Engine::windowUpdate()
    {
        if (this->stage) this->stage->_updateWindow();
    }



    void Engine::engineUpdate()
    {
        if (this->physicsEngine) this->physicsEngine->update();
        if (this->stage) this->stage->update();

    }



    void Engine::stop()
    {
        // glfwSetWindowShouldClose(this->window->_glfwWindow, true);
        this->gameRunningState = false;
    }



    void Engine::release()
    {
        // Stage
        this->stage->release();
        glfwTerminate();

        // Renderer
        this->renderer->release();

    }



    void Engine::registerRenderer(graphics::Renderer* in_renderer)
    {
        if (this->renderer) this->renderer->engine = nullptr;
        in_renderer->engine = this;
        this->renderer = in_renderer;
    }



    void Engine::registerStage(device::Stage* in_stage)
    {
        if (this->stage) this->stage->engine = nullptr;
        in_stage->engine = this;
        this->stage = in_stage;
    }



    void Engine::registerPhysicsEngine(physics::PhysicsEngine* in_physicsEngine)
    {
        if (!in_physicsEngine) return;
        in_physicsEngine->engine = this;
        this->physicsEngine = in_physicsEngine;
    }



}