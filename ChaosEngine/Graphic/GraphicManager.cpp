#pragma once

#include "Common.h"

namespace Chaos::Graphic {

    GraphicManager::GraphicManager(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("GraphicManager");
    }

    GraphicManager::~GraphicManager()
    {

    }

}