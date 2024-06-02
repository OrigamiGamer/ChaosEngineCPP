#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Manager {

        class TextureManager {
        public:
            std::vector<std::wstring> vec_regName;
            std::vector<Type::Texture> vec_tex;

            TextureManager();
            HRESULT Release();
            HRESULT CreateTextureFromFile(std::wstring fileName, std::wstring regName, Type::Texture** out_pTexture);
            Type::Texture* GetTexture(std::wstring regName);

        } Texture;

    }

}
