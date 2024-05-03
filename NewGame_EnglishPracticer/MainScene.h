#pragma once
#include "NewGame.h"

class MainScene : public SceneModel {
    Type::Camera camera;
    Type::VirtKeyStateBuffer VKBuffer;
    ObjectList::Text text;
    ObjectList::Image image_player;
    ObjectList::Image image_bg;
    CompList::EaseFunc<float> ease_x;
    CompList::EaseFunc<float> ease_y;
    
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
