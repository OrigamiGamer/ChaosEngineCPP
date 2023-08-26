#pragma once
#include "NewGame.h"

class MainScene : public SceneModel {
    CompList::Timer timer;

public:
    MainScene();

    int Init();
    int Update();
    int Render();
    int Release();
    int OnSceneEntered();
    bool OnSceneExiting();

} main_scene;
