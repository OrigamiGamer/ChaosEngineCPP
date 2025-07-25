#pragma once

#include "Common.h"

namespace Chaos::Graphic {

    Bitmap::Bitmap()
    {

    }

    Bitmap::~Bitmap()
    {
        std::cout << "啊~雅蔑蝶~ bitmap 被销毁惹啦！！~~ -> "<< this->_d2dbitmap << std::endl;
    }

    vec2<float> Bitmap::getSize()
    {
        if (!this->_d2dbitmap) return vec2<float>(0, 0);
        return vec2<float>(this->_d2dbitmap->GetSize().width, this->_d2dbitmap->GetSize().height);
    }

}