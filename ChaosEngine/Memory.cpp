#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    template <class T>
    void SafeRelease(T** ppT)
    {
        if (*ppT)
        {
            (*ppT)->Release();
            *ppT = NULL;
        }
    };

}
