#pragma once
#include "DebugScene.h"

DebugScene::DebugScene() {

};
void DebugScene::Init() {

};
void DebugScene::Update() {

    if (GetKeyState('F') < 0) {
        Stage::SwitchScene(main_scene);
    }

};
void DebugScene::Render() {

};
void DebugScene::Release() {

};
int DebugScene::OnSceneEntered() {

    return 0;
};
bool DebugScene::OnSceneExiting() {

    return true;
};
