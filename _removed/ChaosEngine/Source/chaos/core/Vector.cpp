#include "chaos/chaos.h"


namespace chaos {



    inline vec2<int> vecf2i(vec2<float>& vecf)
    {
        return vec2<int>(static_cast<int>(vecf.x), static_cast<int>(vecf.y));
    }



    inline vec3<int> vecf2i(vec3<float>& vecf)
    {
        return vec3<int>(static_cast<int>(vecf.x), static_cast<int>(vecf.y), static_cast<int>(vecf.z));
    }



    inline vec2<float> veci2f(vec2<int>& vecf)
    {
        return vec2<float>(static_cast<float>(vecf.x), static_cast<float>(vecf.y));
    }



    inline vec3<float> veci2f(vec3<int>& vecf)
    {
        return vec3<float>(static_cast<float>(vecf.x), static_cast<float>(vecf.y), static_cast<float>(vecf.z));
    }



}