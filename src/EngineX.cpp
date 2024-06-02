#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace EngineX {

        Type::EngineStartupProperty* pStartupProp = nullptr;
        long double lastTime = 0;
        long double curTime = 0;
        long double deltaTime = 0;

        HRESULT Initialize(Type::EngineStartupProperty& EngineProp, Type::WindowInitialProperty& WndProp) {
            pStartupProp = &EngineProp;
            WindowX::InitializeGameWindow(WndProp);
            WindowX::StartMessageLoop();    // Start Message Loop

            return TRUE;
        }

        // Engine Init
        HRESULT EngineInit() {
            HRESULT hr = S_OK;
            hr = GraphicX::InitializeGraphicX();
            EngineX::pStartupProp->pGameMain();    // Call GameMain function

            return hr;
        }

        // Engine Update
        HRESULT EngineUpdate() {
            if (EngineX::lastTime == 0) {
                EngineX::curTime = (long double)((long double)GetTickCount64() / 1000);
                EngineX::lastTime = EngineX::curTime;
            };

            Stage::StageUpdate();

            EngineX::curTime = (long double)((long double)GetTickCount64() / 1000);
            EngineX::deltaTime = EngineX::curTime - EngineX::lastTime;
            EngineX::lastTime = EngineX::curTime;
            return S_OK;
        }

        // Engine Render
        HRESULT EngineRender() {
            DirectX::pHwndRenderTarget->BeginDraw();
            DirectX::pHwndRenderTarget->Clear();

            Stage::StageRender();

            DirectX::pHwndRenderTarget->EndDraw();
            ValidateRect(WindowX::Prop::hWnd, nullptr);
            return S_OK;
        }

        // Engine Exit
        HRESULT EngineExit() {
            if (!EngineX::pStartupProp->pGameExit())  // FALSE returned means no exiting, other values returned will be ignored.
                return FALSE;

            GraphicX::ReleaseGraphicX();

            std::cout << "Engine has exited!" << std::endl;
            return TRUE;    // TRUE returned means confirm exiting.
        }

    }

}
