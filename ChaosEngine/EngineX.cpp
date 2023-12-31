#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* EngineX, the process of engine logic */
    namespace EngineX {

        // Engine Init
        LRESULT EngineInit() {
            LRESULT lr = S_OK;
            lr = GraphicX::GraphicXInit();
            
            lr = Property::Engine::StartupProp->pGameMain();    // Call GameMain function

            return lr;
        };

        // Engine Update
        LRESULT EngineUpdate() {
            static float CurTime;
            if (Property::Engine::LastTime == 0) {
                CurTime = (float)GetTickCount() / 1000;
                Property::Engine::LastTime = CurTime;
            };

            Stage::StageUpdate();

            CurTime = (float)GetTickCount() / 1000;
            Property::Engine::DeltaTime = CurTime - Property::Engine::LastTime;
            Property::Engine::LastTime = CurTime;
            return S_OK;
        };

        // Engine Render
        LRESULT EngineRender() {
            WindowX::pHwndRenderTarget->BeginDraw();
            WindowX::pHwndRenderTarget->Clear();

            Stage::StageRender();

            WindowX::pHwndRenderTarget->EndDraw();
            ValidateRect(Property::Window::hWnd, NULL);
            return S_OK;
        };

        // Engine Exit
        LRESULT EngineExit() {
            if (!Property::Engine::StartupProp->pGameExit())  // FALSE returned means no exiting, other values returned will be ignored.
                return FALSE;

            GraphicX::GraphicXRelease();

            std::cout << "Engine has exited!" << std::endl;
            return TRUE;    // TRUE returned means confirm exiting.
        };

    }

}
