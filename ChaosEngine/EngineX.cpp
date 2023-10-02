#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* EngineX, the process of engine logic */
    namespace EngineX {

        // Global
        std::vector<Model::SceneModel*> pSceneArray;

        Model::SceneModel* pCurScene = NULL;    // Current Scene
        Model::SceneModel* pNextScene = pCurScene;  // Next Scene


        // Engine Init
        LRESULT EngineInit() {
            LRESULT lr = S_OK;
            lr = IGraphic::Init();

            lr = Property::Engine::StartupProp->pGameMain();

            return lr;
        };


        // Engine Update
        LRESULT EngineUpdate() {
            if (pCurScene == pNextScene) {
                if (pCurScene) pCurScene->Update();
            }
            else if (pCurScene->OnSceneExiting()) { // User confirms closing the current scene.
                if (pNextScene) pNextScene->Update();
                pCurScene = pNextScene;
            }

            return S_OK;
        };


        // Engine Render
        LRESULT EngineRender() {
            WindowX::pHwndRenderTarget->BeginDraw();
            WindowX::pHwndRenderTarget->Clear();

            if (pCurScene) {
                pCurScene->Render();
            }

            WindowX::pHwndRenderTarget->EndDraw();
            ValidateRect(Property::Window::hWnd, NULL);
            return S_OK;
        };


        // Engine Exit
        LRESULT EngineExit() {
            if (!Property::Engine::StartupProp->pGameExit())  // FALSE returned means no exiting, other values returned will be ignored.
                return FALSE;

            IGraphic::Release();

            std::cout << "Engine has exited!" << std::endl;
            return TRUE;    // TRUE returned means confirm exiting.
        };

    }

}
