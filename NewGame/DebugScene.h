#pragma once
#include "NewGame.h"

class DebugScene : public SceneModel {

public:
    DebugScene();

    int Init();
    int Update();
    int Render();
    int Release();
    int OnSceneEntered();
    bool OnSceneExiting();

} debug_scene;
