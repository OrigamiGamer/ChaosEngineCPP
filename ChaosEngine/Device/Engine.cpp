#pragma once

#include "Common.h"

namespace Chaos::Device {
    Engine::Engine()
    {
        this->INIT("Engine");
        this->renderer = nullptr;
        this->window = nullptr;
        this->stage = nullptr;
    }

    Engine::~Engine()
    {
        // !! 任何 设备对象 都必须隶属于特定 引擎对象，所以 设备对象共享 将不可用。(多窗口对象共享 将不可用!) !!
        // 可行措施: 设备对象控制权 交予 用户，而非 引擎对象...
        // ( 也许至少现在，我们并不奢求 共享设备对象 ? )
    }

    bool Engine::createRenderer(Chaos::shared_ptr<Graphic::Renderer>* out_renderer)
    {
        if (!this->renderer.has_value()) {
            this->renderer = new Graphic::Renderer(this);
            if (out_renderer != nullptr) out_renderer = &this->renderer;
            return true;
        }
        return false;
    }

    bool Engine::createWindow(Chaos::shared_ptr<Device::Window>* out_window)
    {
        if (!this->window.has_value()) {
            this->window = new Device::Window(this);
            if (out_window != nullptr) out_window = &this->window;
            return true;
        }
        return false;
    }

    bool Engine::createStage(Chaos::shared_ptr<Content::Stage>* out_stage)
    {
        if (!this->stage.has_value()) {
            this->stage = new Content::Stage(this);
            if (out_stage != nullptr) out_stage = &this->stage;
        }
        return false;
    }

    bool Engine::initialize()
    {
        if (!this->createRenderer()) return false;
        if (!this->createWindow()) return false;
        if (!this->createStage()) return false;

        if (!glfwInit()) return false;

        return true;
    }

    void Engine::release()
    {
        this->renderer.release();
        this->window.release();
        this->stage.release();
    }
}