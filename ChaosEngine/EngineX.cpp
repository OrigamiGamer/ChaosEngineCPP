#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace EngineX {

        Type::EngineStartupProperty* pStartupProp = nullptr;
        long double lastTime = 0;
        long double curTime = 0;
        long double deltaTime = 0;

        HRESULT Initialize(Type::EngineStartupProperty& EngineProp, Type::WindowInitialProperty& WndProp) {
            HRESULT hr = NULL;
            pStartupProp = &EngineProp;
            WindowX::InitializeGameWindow(WndProp);
            WindowX::StartMessageLoop();    // Start Message Loop

            return TRUE;
        }

        // Engine Init
        LRESULT EngineInit() {
            LRESULT lr = NULL;
            lr = GraphicX::InitializeGraphicX();
            lr = pStartupProp->pGameMain();    // Call GameMain function

            return S_OK;
        }

        // Engine Update
        LRESULT EngineUpdate() {
            static long double curTime;
            if (EngineX::lastTime == 0) {
                curTime = (long double)((long double)GetTickCount64() / 1000);
                EngineX::lastTime = curTime;
            };

            Stage::StageUpdate();

            curTime = (long double)((long double)GetTickCount64() / 1000);
            EngineX::deltaTime = curTime - EngineX::lastTime;
            EngineX::lastTime = curTime;
            return S_OK;
        }

        // Engine Render
        LRESULT EngineRender() {
            DirectX::pHwndRenderTarget->BeginDraw();
            DirectX::pHwndRenderTarget->Clear();

            Stage::StageRender();

            DirectX::pHwndRenderTarget->EndDraw();
            ValidateRect(WindowX::Prop::hWnd, nullptr);
            return S_OK;
        }

        // Engine Exit
        LRESULT EngineExit() {
            if (!EngineX::pStartupProp->pGameExit())  // FALSE returned means no exiting, other values returned will be ignored.
                return FALSE;

            GraphicX::ReleaseGraphicX();

            std::cout << "Engine has exited!" << std::endl;
            return TRUE;    // TRUE returned means confirm exiting.
        }

    }
    
}