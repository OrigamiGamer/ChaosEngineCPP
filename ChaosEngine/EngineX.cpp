#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* EngineX for processing engine logic */
    namespace EngineX {

        // Global
        std::vector<Model::SceneModel*> pSceneArray;

        Model::SceneModel* pCurScene = NULL;    // Current Scene
        Model::SceneModel* pNextScene = pCurScene;  // Next Scene

        namespace SafeAccessScene {

            LRESULT InitScene(Model::SceneModel* new_scene) {
                if (new_scene != NULL) {
                    ((Model::SceneModel*)new_scene)->Init();
                }
                else return FALSE;

                return TRUE;
            };

            LRESULT UpdateScene(Model::SceneModel* new_scene) {
                if (new_scene != NULL) {
                    new_scene->Update();
                }
                else return FALSE;

                return TRUE;
            };

            LRESULT RenderScene(Model::SceneModel* new_scene) {
                if (new_scene != NULL) {
                    new_scene->Render();
                }
                else return FALSE;

                return TRUE;
            };

        };


        // Engine Init
        LRESULT EngineInit() {
            Engine::IGraphic::Init();

            return 0;
        };


        // Engine Update
        LRESULT EngineUpdate() {
            if (pCurScene == pNextScene) {
                SafeAccessScene::UpdateScene(pCurScene);
            }
            else if (pCurScene->OnSceneExiting()) {
                SafeAccessScene::InitScene(pNextScene);
                pCurScene = pNextScene;
            }

            return 0;
        };


        // Engine Render
        LRESULT EngineRender() {
            WindowX::pHwndRenderTarget->BeginDraw();
            WindowX::pHwndRenderTarget->Clear();

            SafeAccessScene::RenderScene(pCurScene);

            WindowX::pHwndRenderTarget->EndDraw();
            ValidateRect(Property::Window::hWnd, NULL);
            return 0;
        };


        // Engine Exit
        LRESULT EngineExit() {
            if (!Property::Engine::StartupProp->pEngineExit())  // Ignore any other value returned.
                return FALSE;

            Engine::IGraphic::Release();

            std::cout << "Engine has exited!" << std::endl;
            return TRUE;    // TRUE returned means confirm to exit.
        };

    }

}
