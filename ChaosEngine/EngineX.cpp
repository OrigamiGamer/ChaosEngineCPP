#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* EngineX for processing engine logic */
    namespace EngineX {


        // Global
        std::vector<Model::Scene*> pSceneArray;
        Model::Scene* pCurrentScene = NULL;
        Model::Scene* pNextScene = pCurrentScene;


        // Engine Init
        LRESULT EngineInit() {
            Engine::IGraphic::Init();

            if (pCurrentScene != NULL) pCurrentScene->Init();

            return 0;
        };


        // Engine Update
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


        // Engine Render
        LRESULT EngineRender() {
            WindowX::pHwndRenderTarget->BeginDraw();
            WindowX::pHwndRenderTarget->Clear();

            if (pCurrentScene != NULL) pCurrentScene->Render();

            WindowX::pHwndRenderTarget->EndDraw();
            ValidateRect(Property::Window::hWnd, NULL);
            return 0;
        };


        // Engine Exit
        LRESULT EngineExit() {
            if (!Property::Engine::StartupProp->pEngineExit())
                return FALSE;

            Engine::IGraphic::Release();

            std::cout << "Engine has exited!" << std::endl;
            return TRUE;
        };


    }

}
