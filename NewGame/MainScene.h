#pragma once
#include "NewGame.h"

class MainScene : public SceneModel {
    CompList::Timer timer;
    ID2D1Bitmap* pD2DBitmap;

public:
    MainScene();

    int Init();
    int Update();
    int Render();
    int Release();
    int OnSceneEntered();
    bool OnSceneExiting();

} main_scene;
