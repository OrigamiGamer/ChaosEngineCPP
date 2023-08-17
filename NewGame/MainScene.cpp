#pragma once
#include "MainScene.h"

int MainScene::Init() {


    return 0;
};
int MainScene::Update() {
    cout << "this is MainScene!!!" << endl;

    if (GetKeyState('D') < 0) {
        Engine::Stage::SwitchScene(&debug_scene);
    }


    return 0;
};
int MainScene::Render() {


    return 0;
};
int MainScene::Release() {


    return 0;
};

int MainScene::OnSceneEntered() {
    
    return 0;
};

bool MainScene::OnSceneExiting() {
    
    return true;
};
