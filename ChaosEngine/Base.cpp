#pragma once

#include "Common.h"

namespace Chaos {
    Base::Base()
    {
        this->INIT("Base");
    }

    Base::~Base()
    {
        std::cout << "release -> " << this->nameId.c_str() << std::endl;
    }

    void Base::INIT(std::string new_nameId)
    {
        this->nameId = new_nameId;
        this->nameIdHeap.push_back(new_nameId);
        std::cout << "init -> " << this->nameId.c_str() << std::endl;
    }
}