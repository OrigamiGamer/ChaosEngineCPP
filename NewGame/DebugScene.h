#pragma once
#include "NewGame.h"

class DebugScene : public SceneModel {

public:
    DebugScene();

    void Init();
    void Update();
    void Render();
    void Release();
    int OnSceneEntered();
    bool OnSceneExiting();

} debug_scene;
