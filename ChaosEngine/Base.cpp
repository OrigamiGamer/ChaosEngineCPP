#pragma once

#include "Common.h"

namespace Chaos {
    Base::Base()
    {
        this->INIT("Base");
    }

    Base::~Base()
    {
        std::cout << "[CALL] " << this->GET_TOP_TYPE().c_str() << " -> Base::~Base()" << std::endl;
    }

    inline void Base::INIT(std::string new_typeId)
    {
        this->typeHeap.push_back(new_typeId);
        std::cout << "init -> " << new_typeId.c_str() << std::endl;
    }

    inline void Base::SET_NAME(std::string new_nameId)
    {
        this->name = new_nameId.empty() ? "Unnamed" : new_nameId;
    }

    const inline size_t Base::GET_TYPE_DEPTH()
    {
        return this->typeHeap.size();
    }

    const std::string Base::GET_TOP_TYPE()
    {
        return typeHeap.at(this->GET_TYPE_DEPTH() - 1);
    }

    std::string Base::GET_GUID()
    {
        // generate from all properties of this object        
        // TODO
        return {};
    }
}