#pragma once
#include "NewGame.h"

class MainScene : public Scene {
    // ID2D1SolidColorBrush* brush;

    int Init();
    int Update();
    int Render();
    int Release();
    int OnSceneEntered();
    bool OnSceneExiting();

} main_scene;
