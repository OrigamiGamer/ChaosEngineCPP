#pragma once

#include "Common.h"

namespace Chaos::Graphic {
    GraphicManager::GraphicManager(Device::Engine* new_engine)
    {
        this->engine = new_engine;
    }

    GraphicManager::~GraphicManager()
    {

    }
}