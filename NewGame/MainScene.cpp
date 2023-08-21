#pragma once
#include "MainScene.h"

MainScene::MainScene() {

}

int MainScene::Init() {

    return 0;
};
int MainScene::Update() {

    if (GetKeyState('D') < 0) {
        Engine::Stage::SwitchScene(&debug_scene);
    }


    return 0;
};
int MainScene::Render() {

    Engine::IGraphic::SetStrokeWidth(10);
    Engine::IGraphic::DrawLine({ 50,50 }, { 200,100 });


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
