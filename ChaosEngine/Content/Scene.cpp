#pragma once

#include "Common.h"

namespace Chaos::Content {
    Scene::Scene(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("Scene");

    }

    Scene::~Scene()
    {

    }
}