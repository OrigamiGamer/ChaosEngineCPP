#pragma once

#include "Common.h"

namespace Chaos::Content {
    Scene::Scene(Device::Engine* new_engine)
    {
        this->engine = new_engine;

    }

    Scene::~Scene()
    {

    }
}