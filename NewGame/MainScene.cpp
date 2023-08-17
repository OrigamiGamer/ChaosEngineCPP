#pragma once
#include "MainScene.h"

int MainScene::Init() {


    return 0;
};
int MainScene::Update() {
    cout << "this is MainScene!!!" << endl;

    if (GetKeyState('D') > 1) {
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
