#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* EngineX for processing engine logic */
    namespace EngineX {


        namespace _Internal {

            void InitComp(Model::CompModel& AnyComp) {
              
                const std::string type_Comp = typeid(Model::CompModel).name();
                const std::string type_Object = typeid(Model::ObjectModel).name();
                const std::string type_Scene = typeid(Model::SceneModel).name();

                std::string new_type = typeid(AnyComp).name();
                
                if (new_type == type_Comp) {
                    
                }
                else if (new_type == type_Object) {

                }
                else if (new_type == type_Scene) {
                    
                }
            };

            void UpdateComp(Model::CompModel& AnyComp) {

            };

            void RenderComp(Model::CompModel& AnyComp) {

            };

            void ReleaseComp(Model::CompModel& AnyComp) {
            };

        };


        // Global
        std::vector<Model::SceneModel*> pSceneArray;
        Model::SceneModel* pCurrentScene = NULL;
        Model::SceneModel* pNextScene = pCurrentScene;


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
            return TRUE;    // TRUE returned means confirm to exit.
        };

    }

}
