#pragma once
#include "ChaosEngine.h"
#include "Engine.h"

namespace ChaosEngine {

    /* Engine */
    namespace Engine {

        BOOL Start(Type::WindowInitialProperty* WndProp, Type::EngineStartupProperty* EngineProp) {
            WindowX::InitWindow(WndProp);
            Property::Engine::StartupProp = EngineProp;

            WindowX::StartMessageLoop();

            return true;
        };

        BOOL Release() {
            WindowX::ReleaseDirectX();

            return true;
        };



        namespace Stage {

            void SwitchScene(Model::SceneModel* pTargetScene) {
                if (pTargetScene != NULL)
                    EngineX::pNextScene = pTargetScene;
            };

            void RegScene(Model::SceneModel* pAnyScene) {
                if (pAnyScene != NULL) {
                    if (EngineX::pCurrentScene == NULL) {
                        EngineX::pCurrentScene = pAnyScene;
                        EngineX::pNextScene = EngineX::pCurrentScene;   // Switch to initial scene directly
                    }

                    EngineX::pSceneArray.push_back(pAnyScene);  // Register the new scene
                }

            };

        }



        // Basic Interfaces of Graphics
        namespace IGraphic {

            ID2D1SolidColorBrush* pBrush = NULL;
            float StrokeWidth = 1;

            LRESULT Init() {
                D2D1_BRUSH_PROPERTIES brush_properties = D2D1_BRUSH_PROPERTIES();
                brush_properties.opacity = 1;
                brush_properties.transform = D2D1::IdentityMatrix();

                WindowX::pHwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGreen), brush_properties, &pBrush);


                return 0;
            };

            LRESULT Release() {
                LRESULT lr = NULL;
                lr = pBrush->Release();
                return lr;
            };

            void SetColor(Type::Color newColor) {
                pBrush->SetColor(D2D1::ColorF(newColor.rgb, newColor.alpha));
            };

            void SetStrokeWidth(FLOAT newStrokeWidth) {
                if (newStrokeWidth >= 0) StrokeWidth = newStrokeWidth;
            };

            void DrawLine(Type::POS pos_1, Type::POS pos_2) {
                WindowX::pHwndRenderTarget->DrawLine({ pos_1.x, pos_1.y }, { pos_2.x, pos_2.y }, pBrush, StrokeWidth);
            };

            void DrawRectangle(Type::POS pos, Type::SIZE size, Type::POS radius) {
                D2D1_RECT_F rect{ pos.x, pos.y, pos.x + size.width, pos.y + size.height };
                WindowX::pHwndRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(rect, radius.x, radius.y), pBrush);
            };

        }

    }

}
