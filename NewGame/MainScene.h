#pragma once
#include "NewGame.h"

class MainScene : public SceneModel {
    Type::Camera camera;
    Type::VirtKeyStateBuffer vk_state_buffer;
    CompList::Timer timer;
    vector<ObjectList::Image> vec_image;
    ObjectList::Text text;
    ObjectList::Image image_bg;
    CompList::EaseFunc<float> ease;

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

} main_scene;
