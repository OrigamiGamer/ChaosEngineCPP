#pragma once

#include "Class/Graphics/Graphics.h"



namespace Chaos::Graphics {



    struct Color {
        float r, g, b;

        Color(float r = 0, float g = 0, float b = 0);
        Color(float rgb = 0);
    };



}