#pragma once
#include "ManagerList.h"

namespace ChaosEngine {

    namespace Manager {

        TextureManager::TextureManager() {
            vec_regName;
            vec_tex;
        };

        // Create a texture from a file
        HRESULT TextureManager::CreateTextureFromFile(std::wstring fileName, std::wstring regName = L"", Type::Texture** lpTexture = NULL) {
            HRESULT hr = NULL;

            IWICBitmapDecoder* pDecoder = NULL;
            hr = WindowX::pWICFactory->CreateDecoderFromFilename((LPWSTR)fileName.data(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
            if (FAILED(hr)) return hr;

            IWICBitmapFrameDecode* pFrame = NULL;
            hr = pDecoder->GetFrame(0, &pFrame); if (FAILED(hr)) return hr;

            IWICFormatConverter* pConverter = NULL;
            hr = WindowX::pWICFactory->CreateFormatConverter(&pConverter); if (FAILED(hr)) return hr;
            pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeCustom);

            Type::Texture _tex;
            if (SUCCEEDED(WindowX::pHwndRenderTarget->CreateBitmapFromWicBitmap((IWICBitmapSource*)pConverter, &_tex.pD2DBitmap))) {
                if (regName == L"") regName = std::to_wstring(vec_tex.size() + 1);
                vec_regName.push_back(regName);
                vec_tex.push_back(_tex);
                if (lpTexture) *lpTexture = &vec_tex[vec_tex.size() - 1];
            }

            pConverter->Release();
            pFrame->Release();
            pDecoder->Release();

            return hr;
        };

        // Release the TextureManager
        HRESULT TextureManager::Release() {
            for (UINT i = 0; i < vec_tex.size(); i++)
                if (!vec_tex[i].pD2DBitmap) vec_tex[i].pD2DBitmap->Release();
            vec_tex.clear();
            return S_OK;
        };

        // Get a pTexture by a RegName
        Type::Texture* TextureManager::GetTexture(std::wstring regName) {
            if (regName != L"")
                for (UINT i = 0; i < vec_regName.size(); i++)
                    if (vec_regName[i] == regName) {
                        return &vec_tex[i];
                    }
            return NULL;
        }

    }

}
