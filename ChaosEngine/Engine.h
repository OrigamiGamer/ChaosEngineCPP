#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Engine */
    namespace Engine {

        BOOL Start(Type::WindowInitialProperty* WndProp, Type::EngineStartupProperty* EngineProp);
        BOOL Release();



        namespace Stage {

            void SwitchScene(Model::Scene* pTargetScene);
            void RegScene(Model::Scene* pAnyScene);

        }



        namespace IGraphic {

            extern ID2D1SolidColorBrush* pBrush;
            extern float StrokeWidth;

            LRESULT Init();
            LRESULT Release();
            void SetColor(Type::Color newColor);
            void SetLineWidth(float newStrokeWidth);
            void DrawLine(Type::POS pos_1, Type::POS pos_2);

        }

    }

}