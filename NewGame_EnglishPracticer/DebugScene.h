#pragma once
#include "NewGame.h"

class DebugScene;

class DebugScene : public SceneModel {

public:
    DebugScene();

    void Init();
    void Update();
    void Render();
    void Release();
    int OnSceneEntered();
    bool OnSceneExiting();

} scene_debug;
