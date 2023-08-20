#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* EngineX for processing engine logic */
    namespace EngineX {

        // Global
        std::vector<Model::Scene*> pSceneArray;
        Model::Scene* pCurrentScene = NULL;
        Model::Scene* pNextScene = pCurrentScene;

        LRESULT EngineInit() {
            Engine::IGraphic::Init();

            if (pCurrentScene != NULL) pCurrentScene->Init();

            return 0;
        };

        LRESULT EngineUpdate() {
            if (pCurrentScene != NULL) {
                if (pCurrentScene == pNextScene) {
                    pCurrentScene->Update();

                } else if (pCurrentScene->OnSceneExiting()) {
                    pCurrentScene = pNextScene;
                    pCurrentScene->Init();
                }
            }

            return 0;
        };

        LRESULT EngineRender() {
            OutputDebugString("begin drawing\n");
            WindowX::pHwndRenderTarget->BeginDraw();
            WindowX::pHwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

            if (pCurrentScene != NULL) pCurrentScene->Render();

            WindowX::pHwndRenderTarget->EndDraw();
            ValidateRect(Property::Window::hWnd, NULL);
            return 0;
        };

        LRESULT EngineExit() {
            if (!Property::Engine::StartupProp->pEngineExit())
                return FALSE;

            Engine::IGraphic::Release();

            std::cout << "Engine has exited!" << std::endl;

            return TRUE;
        };

    }

}
