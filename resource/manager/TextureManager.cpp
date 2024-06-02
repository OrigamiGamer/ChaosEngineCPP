#pragma once
#include "ResList.cpp"

namespace ChaosEngine {

    namespace Manager {

        TextureManager::TextureManager() {
            vec_regName;
            vec_tex;
        }

        // Release all texture resources.
        HRESULT TextureManager::Release() {
            for (UINT i = 0; i < vec_tex.size(); i++)
                if (!vec_tex[i].pD2DBitmap) vec_tex[i].pD2DBitmap->Release();
            vec_tex.clear();
            return S_OK;
        }

        // Create a texture resource from an image file.
        HRESULT TextureManager::CreateTextureFromFile(
            std::wstring fileName, std::wstring regName = L"", Type::Texture** out_pTexture = nullptr
        ) {
            HRESULT hr = S_OK;

            IWICBitmapDecoder* pDecoder = nullptr;
            hr = DirectX::pWICFactory->CreateDecoderFromFilename(
                locate(fileName).c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder
            ); if (FAILED(hr)) return hr;

            IWICBitmapFrameDecode* pFrame = nullptr;
            hr = pDecoder->GetFrame(0, &pFrame); if (FAILED(hr)) return hr;

            IWICFormatConverter* pConverter = nullptr;
            hr = DirectX::pWICFactory->CreateFormatConverter(&pConverter); if (FAILED(hr)) return hr;
            pConverter->Initialize(
                pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeCustom
            );

            size_t n = vec_tex.size() + 1;
            vec_tex.resize(n);
            Type::Texture& _tex = vec_tex[n - 1];
            if (SUCCEEDED(DirectX::pHwndRenderTarget->CreateBitmapFromWicBitmap(pConverter, &_tex.pD2DBitmap))) {
                if (regName == L"") {
                    vec_regName.push_back(std::to_wstring(n));  // Need to check for duplicates.
                }
                else {
                    vec_regName.push_back(regName);
                }
                if (out_pTexture) *out_pTexture = &_tex; 
            }
            else {
                vec_tex.pop_back();
            }

            SafeRelease(&pConverter);
            SafeRelease(&pFrame);
            SafeRelease(&pDecoder);
            return hr;
        }

        // Get a pTexture by the register name of a texture resource.
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
