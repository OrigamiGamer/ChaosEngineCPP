#pragma once

#include "GameObject/GameObject.h"

namespace Chaos::GameObject {



    Actor::Actor(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("Actor");

    }



    Actor::~Actor()
    {
        
    }


    
}