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
        this->typeIdHeap.push_back(new_nameId);
        std::cout << "init -> " << this->nameId.c_str() << std::endl;
    }

    inline size_t Base::GET_TYPE_DEPTH()
    {
        return this->typeIdHeap.size();
    }

    inline std::string Base::GET_TOP_TYPE()
    {
        return typeIdHeap.at(this->GET_TYPE_DEPTH() - 1);
    }
}