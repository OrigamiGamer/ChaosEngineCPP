#pragma once

#include "ChaosEngine.h"

namespace Chaos {



    Base::Base()
    {
        this->INIT("Base");
    }



    Base::~Base()
    {
        std::cout << "[CALL] " << this->GET_TOP_TYPE().c_str() << " -> Base::~Base()" << std::endl;
    }



    void Base::release()
    {
        std::cout << "[CALL] " << this->GET_TOP_TYPE().c_str() << " -> Base::release()" << std::endl;
    }



    inline void Base::INIT(std::string new_typeId)
    {
        this->typeHeap.push_back(new_typeId);
        std::cout << "[CALL] " << new_typeId.c_str() << " -> Base::INIT(...)" << std::endl;
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
        // TODO
        // generate it by all properties of this object
        return {};
    }



}
