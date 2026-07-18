#include "chaos/chaos.h"

namespace chaos {



    Base::Base()
    {
        this->INIT("Base");
    }



    Base::~Base()
    {
        // std::cout << "[CALL] " << this->GET_TOP_TYPE().c_str() << " -> Base::~Base()" << std::endl;
    }



    void Base::release()
    {
        // std::cout << "[CALL] " << this->GET_TOP_TYPE().c_str() << " -> Base::release()" << std::endl;
    }



    inline void Base::INIT(std::string in_typeId)
    {
        this->typeIdList.push_back(in_typeId);

        std::cout << "[CALL] " << in_typeId.c_str() << " -> Base::INIT(...)" << std::endl;
    }



    inline void Base::SET_NAME(std::string in_nameId)
    {
        this->nameId = in_nameId.empty() ? "Unnamed" : in_nameId;
    }



    const inline size_t Base::GET_TYPE_DEPTH()
    {
        return 0;
    }



    const std::string Base::GET_TOP_TYPE()
    {
        size_t _size = this->GET_TYPE_DEPTH();
        if (_size == 0) return "<EMPTY-TYPE-ERROR>";
        return typeIdList.at(_size - 1);
    }



    std::string Base::GET_GUID()
    {
        // TODO
        // generate it by all properties of this object
        return {};
    }



}
