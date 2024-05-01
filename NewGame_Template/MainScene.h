#pragma once
#include "NewGame.h"

class MainScene : public SceneModel {
    Type::Camera camera;

public:
    MainScene();

    void Init();
    void Update();
    void Render();
    void Release();
    int OnSceneEntered();
    int OnCameraEntered();
    bool OnSceneExiting();
    bool OnCameraExiting();

} scene_main;
