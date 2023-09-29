#pragma once
#include "ManagerList.h"

namespace ChaosEngine {

    namespace TextureManager {

        extern std::vector<LPWSTR> vec_regName;
        extern std::vector<Type::Texture> vec_tex;

        HRESULT CreateTextureFromFile(LPWSTR fileName, LPWSTR regName = L"");
        Type::SIZE GetSize();
        HRESULT Release();

    }

}
