#pragma once
#include "ManagerList.h"

namespace ChaosEngine {

    namespace TextureManager {

        std::vector<LPWSTR> vec_regName;
        std::vector<Type::Texture> vec_tex;

        //D:\\origami\\ChaosEngine\\ChaosEngineCPP\\ChaosEngine\\texture\\stonecutter.png

        HRESULT CreateTextureFromFile(LPWSTR fileName, LPWSTR regName = L"") {
            //DWORD HeaderPath = GetModuleFileName(NULL, L"", MAXDWORD);
            HRESULT hr = NULL;

            IWICBitmapDecoder* pDecoder = NULL;
            hr = WindowX::pWICFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
            if (FAILED(hr)) return hr;

            IWICBitmapFrameDecode* pFrame = NULL;
            hr = pDecoder->GetFrame(0, &pFrame); if (FAILED(hr)) return hr;

            IWICFormatConverter* pConverter = NULL;
            hr = WindowX::pWICFactory->CreateFormatConverter(&pConverter); if (FAILED(hr)) return hr;
            pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeCustom);

            Type::Texture _tex;
            if (WindowX::pHwndRenderTarget->CreateBitmapFromWicBitmap(pConverter, &_tex.pD2DBitmap)) {
                if (regName == L"") regName = (LPWSTR)std::to_wstring(vec_tex.size() + 1).data();
                vec_regName.push_back(regName);
                vec_tex.push_back(_tex);
            }

            return hr;
        };

        Type::SIZE GetSize() {
            return Type::SIZE();
        };

        HRESULT Release() {
            for (UINT i = 0; i < vec_tex.size(); i++)
                if (!vec_tex[i].pD2DBitmap) vec_tex[i].pD2DBitmap->Release();
            vec_tex.clear();
            return S_OK;
        };

    }

}
