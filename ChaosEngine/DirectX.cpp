#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace DirectX {

        /* Processes about DirectX */

        // Global
        ID2D1Factory* pD2DFactory = nullptr;
        IWICImagingFactory* pWICFactory = nullptr;
        IDWriteFactory* pDWriteFactory = nullptr;
        ID2D1HwndRenderTarget* pHwndRenderTarget = nullptr;

        // Initialize DirectX
        HRESULT InitializeDirectX(HWND hWnd) {
            HRESULT hr = S_OK;

            /* D2D */

            // D2DFactory
            hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
            if (FAILED(hr)) return hr;

            /* WIC */

            // WICImagingFactory
            hr = CoInitialize(NULL);
            hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));
            
            if (FAILED(hr)) return hr;

            /* DWrite */

            // DWriteFactory
            hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&pDWriteFactory);
            if (FAILED(hr)) return hr;

            hr = DirectX::CreateRenderTarget(hWnd); if (FAILED(hr)) return hr;

            return hr;
        }

        // Create RenderTarget
        HRESULT CreateRenderTarget(HWND hWnd) {
            HRESULT hr = S_OK;
            if (pD2DFactory == nullptr) return E_FAIL;

            D2D1_RENDER_TARGET_PROPERTIES RenderTarget_Properties{};
            //float hWndDpi = GetDpiForWindow(hWnd);
            //RenderTarget_Properties.dpiX = hWndDpi;
            //RenderTarget_Properties.dpiY = hWndDpi;
            RenderTarget_Properties.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
            RenderTarget_Properties.pixelFormat = { DXGI_FORMAT_R8G8B8A8_UNORM ,D2D1_ALPHA_MODE_PREMULTIPLIED };

            D2D1_HWND_RENDER_TARGET_PROPERTIES HwndRenderTarget_properties{};
            HwndRenderTarget_properties.hwnd = hWnd;
            HwndRenderTarget_properties.pixelSize = D2D1::SizeU((int)WindowX::Prop::Size.width, (int)WindowX::Prop::Size.height);   //
            HwndRenderTarget_properties.presentOptions = D2D1_PRESENT_OPTIONS_NONE;

            hr = pD2DFactory->CreateHwndRenderTarget(&RenderTarget_Properties, &HwndRenderTarget_properties, &pHwndRenderTarget);
            if (FAILED(hr)) return hr;
            return hr;
        }

        // Release DirectX
        HRESULT ReleaseDirectX() {

            /* HwndRenderTarget */
            SafeRelease(&pHwndRenderTarget);
            /* DWrite */
            SafeRelease(&pDWriteFactory);
            /* WIC */
            SafeRelease(&pWICFactory);
            /* D2D */
            SafeRelease(&pD2DFactory);

            return 0;
        }

    }

}