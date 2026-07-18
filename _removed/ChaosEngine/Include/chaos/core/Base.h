#pragma once

#include "chaos/chaos.h"


namespace chaos {


    class Base {
    public:
        std::string nameId;
        std::vector<std::string> typeIdList;

        Base();
        ~Base();

        Base(Base&&) = default;
        Base& operator=(Base&&) = default;

        Base(const Base&) = delete;
        Base& operator=(const Base&) = delete;

        virtual void release();

        void INIT(std::string in_typeId);

        void SET_NAME(std::string in_nameId);

        // Get the depth of the type of this object
        // 获取该对象类型的深度。
        const size_t GET_TYPE_DEPTH();

        // Get the type name of this object.
        // 获取该对象顶层类型的名称。
        const std::string GET_TOP_TYPE();

        // Get the Global Unique Identifier(GUID) of this object.
        // 获取该对象的全局唯一标识符(GUID)。
        std::string GET_GUID();

    };


}