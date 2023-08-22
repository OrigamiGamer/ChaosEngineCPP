#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Engine */
    namespace Engine {

        BOOL Start(Type::WindowInitialProperty* WndProp, Type::EngineStartupProperty* EngineProp);
        BOOL Release();



        namespace Stage {

            void SwitchScene(Model::SceneModel* pTargetScene);
            void RegScene(Model::SceneModel* pAnyScene);

        }



        namespace IGraphic {

            extern ID2D1SolidColorBrush* pBrush;
            extern float StrokeWidth;

            LRESULT Init();
            LRESULT Release();
            void SetColor(Type::Color newColor);
            void SetStrokeWidth(FLOAT newStrokeWidth);
            void DrawLine(Type::POS pos_1, Type::POS pos_2);
            void DrawRectangle(Type::POS pos, Type::SIZE size, FLOAT radiusX = 0, FLOAT radiusY = 0);

        }

    }

}