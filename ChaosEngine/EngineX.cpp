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
            WindowX::pHwndRenderTarget->BeginDraw();
            WindowX::pHwndRenderTarget->Clear({ 0,0,0,1 });

            if (pCurrentScene != NULL) pCurrentScene->Render();

            WindowX::pHwndRenderTarget->EndDraw();
            return 0;
        };

        LRESULT EngineExit() {
            std::cout << "Engine has exited!" << std::endl;

            return 0;
        };

    }

}
