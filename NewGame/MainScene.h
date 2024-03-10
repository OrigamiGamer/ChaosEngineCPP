#pragma once
#include "NewGame.h"

class MainScene : public SceneModel {
    Type::Camera camera;
    CompList::Timer timer;
    vector<ObjectList::Image> vec_image;
    ObjectList::Text text;
    ObjectList::Image image_bg;

public:
    MainScene();

    void Init();
    void Update();
    void Render();
    void Release();
    int OnSceneEntered();
    bool OnSceneExiting();

} main_scene;
