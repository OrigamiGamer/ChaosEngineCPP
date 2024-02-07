#pragma once
#include "NewGame.h"

class MainScene : public SceneModel {
    CompList::Timer timer;
    vector<ObjectList::Image> vec_image;

public:
    MainScene();

    void Init();
    void Update();
    void Render();
    void Release();
    int OnSceneEntered();
    bool OnSceneExiting();

} main_scene;
