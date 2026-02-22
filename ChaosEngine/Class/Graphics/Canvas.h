#pragma once

#include "Class/Graphics/Graphics.h"



namespace Chaos::Graphics {



    class Canvas : public Base {
    private:
        ID2D1HwndRenderTarget* _hwndRenderTarget = nullptr; 

    public:
        Canvas();

        void release();

        friend class Graphics::Renderer;
    };



}