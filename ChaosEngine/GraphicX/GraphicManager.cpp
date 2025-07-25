#pragma once

#include "GraphicX/GraphicX.h"

namespace Chaos::GraphicX {

    GraphicManager::GraphicManager(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("GraphicManager");
    }

    GraphicManager::~GraphicManager()
    {

    }

}