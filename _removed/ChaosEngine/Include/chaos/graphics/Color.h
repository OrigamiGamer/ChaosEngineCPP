#pragma once

#include "chaos/graphics/graphics.h"


namespace chaos::graphics {



    struct Color {
        float r, g, b;

        Color(float r = 0, float g = 0, float b = 0);
        Color(float rgb = 0);
    };



}