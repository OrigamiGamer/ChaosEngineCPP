#pragma once

#include "Common.h"

namespace Chaos {

    template<typename T>
    vec2<T>::vec2() {}

    template<typename T>
    vec2<T>::vec2(T x, T y) : x(x), y(y) {}
    
    template<typename T>
    vec3<T>::vec3() {}

    template<typename T>
    vec3<T>::vec3(T x, T y, T z) : x(x), y(y), z(z) {}

}