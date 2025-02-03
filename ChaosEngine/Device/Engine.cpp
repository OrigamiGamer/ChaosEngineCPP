#pragma once

#include "Common.h"

namespace Chaos::Device {
    Engine::Engine()
    {
        this->stage = nullptr;
        this->window = nullptr;
        this->renderer = nullptr;
    }

    Engine::~Engine()
    {

    }

    bool Engine::createRenderer(Chaos::ptr<Graphic::Renderer>* out_renderer)
    {
        if (!this->renderer.has_value()) {
            this->renderer = new Graphic::Renderer(this);
            if (out_renderer != nullptr) out_renderer = &this->renderer;
            return true;
        }
        return false;
    }

    bool Engine::createWindow(Chaos::ptr<Device::Window>* out_window)
    {
        if (!this->window.has_value()) {
            this->window = new Device::Window(this);
            if (out_window != nullptr) out_window = &this->window;
            return true;
        }
        return false;
    }

    void Engine::release()
    {
        renderer.release();
    }
}