#pragma once
#include "DebugScene.h"

DebugScene::DebugScene() {

};

int DebugScene::Init() {


    return 0;
};
int DebugScene::Update() {

    if (GetKeyState('F') < 0) {
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

int DebugScene::OnSceneEntered() {

    return 0;
};

bool DebugScene::OnSceneExiting() {

    return true;
};