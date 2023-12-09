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
            
            lr = Property::Engine::StartupProp->pGameMain();    // Call GameMain function

            return lr;
        };


        // Engine Update
        LRESULT EngineUpdate() {
            float CurTime = (float)GetTickCount() / 1000;
            if (Property::Engine::LastTime == 0) Property::Engine::LastTime = CurTime;

            if (pCurScene == pNextScene) {
                if (pCurScene) {
                    // Update Logic
                    ((Model::SceneModel*)pCurScene)->Update();  // Update the logic in model at first,
                    pCurScene->Update();    // then update the logic of scene.

                    // Update PhysicX
                    PhysicXEngine::PhysicXUpdate(pCurScene->vec_pObject, Property::Engine::DeltaTime);

                };
            }
            else if (pCurScene->OnSceneExiting()) { // User confirms closing the current scene.
                ((Model::SceneModel*)pNextScene)->Update(); // Update in the same way.
                if (pNextScene) pNextScene->Update();
                pCurScene = pNextScene;
            }

            Property::Engine::DeltaTime = CurTime - Property::Engine::LastTime;
            Property::Engine::LastTime = CurTime;
            return S_OK;
        };


        // Engine Render
        LRESULT EngineRender() {
            WindowX::pHwndRenderTarget->BeginDraw();
            WindowX::pHwndRenderTarget->Clear();

            if (pCurScene) {
                ((Model::SceneModel*)pCurScene)->Render();  // Render in the same way to update.
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
