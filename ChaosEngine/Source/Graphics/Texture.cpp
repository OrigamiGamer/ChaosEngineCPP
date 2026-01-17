#pragma once

#include "Class/Graphics/Texture.h"

namespace Chaos::Graphics {



    Texture::Texture(ID2D1Bitmap** new_bitmap)
    {
        this->_bitmap = new_bitmap;
    }



    Texture::Texture()
    {
        
    }



    Texture::~Texture()
    {
        if (this->_bitmap) delete this->_bitmap;
    }



    void Texture::release()
    {
        if (this->_bitmap) System::safeReleaseCOM(*this->_bitmap);

        std::cout << "[CALL] Texture -> release() -> " << this->nameId << std::endl;
    }



    vec2<float> Texture::getSize()
    {
        if (!this->_bitmap) return vec2<float>({ 0, 0 });
        if (!*this->_bitmap) return vec2<float>({ 0, 0 });

        auto& __bitmap = *this->_bitmap;
        return vec2<float>({ __bitmap->GetSize().width, __bitmap->GetSize().height });
    }



}