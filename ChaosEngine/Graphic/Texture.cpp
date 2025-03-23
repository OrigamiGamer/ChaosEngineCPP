#pragma once

#include "Common.h"

namespace Chaos::Graphic {

    Texture::Texture()
    {

    }

    Texture::~Texture()
    {

    }

    vec2<float> Texture::getSize()
    {
        if (!this->bitmap) return vec2<float>({ 0, 0 });
        return vec2<float>({ this->bitmap->GetSize().width, this->bitmap->GetSize().height });
    }

}