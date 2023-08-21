#pragma once
#include "NewGame.h"

class MainScene : public Scene {

public:
    MainScene();

    int Init();
    int Update();
    int Render();
    int Release();
    int OnSceneEntered();
    bool OnSceneExiting();

} main_scene;
