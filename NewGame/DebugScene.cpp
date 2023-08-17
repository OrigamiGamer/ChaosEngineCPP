#pragma once
#include "DebugScene.h"

int DebugScene::Init() {


    return 0;
};
int DebugScene::Update() {
    cout << "this is DebugScene" << endl;

    if (GetKeyState('F') > 1) {
        Engine::Stage::SwitchScene(&main_scene);
    }

    return 0;
};
int DebugScene::Render() {


    return 0;
};
int DebugScene::Release() {


    return 0;
};
