#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* EngineX, the process of engine logic */
    namespace EngineX {

        // Global
        std::vector<Model::SceneModel*> pSceneArray;

        Model::SceneModel* pCurScene = NULL;    // Current Scene
        Model::SceneModel* pNextScene = pCurScene;  // Next Scene

        CompList::PhysicXEngine PhysicXEngine;


        // Engine Init
        LRESULT EngineInit() {
            LRESULT lr = S_OK;
            lr = IGraphic::Init();
            PhysicXEngine.Init();
            
            lr = Property::Engine::StartupProp->pGameMain();

            return lr;
        };


        // Engine Update
        LRESULT EngineUpdate() {
            PhysicXEngine.Update();
            
            if (pCurScene == pNextScene) {
                if (pCurScene) { 
                    ((Model::SceneModel*)pCurScene)->Update();  // Update the logic of Model itself at first,
                    pCurScene->Update();    // then update the logic of Scene.
                };
            }
            else if (pCurScene->OnSceneExiting()) { // User confirms closing the current scene.
                ((Model::SceneModel*)pNextScene)->Update(); // Update in the same way.
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
                PhysicXEngine.Render();
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
            PhysicXEngine.Release();

            std::cout << "Engine has exited!" << std::endl;
            return TRUE;    // TRUE returned means confirm exiting.
        };

    }

}
