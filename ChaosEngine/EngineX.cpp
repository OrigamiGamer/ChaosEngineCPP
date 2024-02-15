#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* EngineX, the process of engine logic */
    namespace EngineX {

        // Engine Init
        LRESULT EngineInit() {
            LRESULT lr = S_OK;
            lr = GraphicX::GraphicXInit();
            
            lr = Properties::Engine::StartupProp->pGameMain();    // Call GameMain function

            return lr;
        };

        // Engine Update
        LRESULT EngineUpdate() {
            static long double curTime;
            if (Properties::Engine::LastTime == 0) {
                curTime = (long double)((long double)GetTickCount64() / 1000);
                Properties::Engine::LastTime = curTime;
            };

            Stage::StageUpdate();

            curTime = (long double)((long double)GetTickCount64() / 1000);
            Properties::Engine::DeltaTime = curTime - Properties::Engine::LastTime;
            Properties::Engine::LastTime = curTime;
            return S_OK;
        };

        // Engine Render
        LRESULT EngineRender() {
            WindowX::pHwndRenderTarget->BeginDraw();
            WindowX::pHwndRenderTarget->Clear();

            Stage::StageRender();

            WindowX::pHwndRenderTarget->EndDraw();
            ValidateRect(Properties::Window::hWnd, nullptr);
            return S_OK;
        };

        // Engine Exit
        LRESULT EngineExit() {
            if (!Properties::Engine::StartupProp->pGameExit())  // FALSE returned means no exiting, other values returned will be ignored.
                return FALSE;

            GraphicX::GraphicXRelease();

            std::cout << "Engine has exited!" << std::endl;
            return TRUE;    // TRUE returned means confirm exiting.
        };

    }

}
