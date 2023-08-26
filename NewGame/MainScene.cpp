#pragma once
#include "MainScene.h"

MainScene::MainScene() {
    timer;
}

int MainScene::Init() {
    this->RegComp(timer);
    timer.Create(100);
    timer.Begin();

    return 0;
};
int MainScene::Update() {

    if (GetKeyState('D') < 0) {
        Engine::Stage::SwitchScene(debug_scene);
    }

    ULONGLONG delta_t;
    if (timer.Todo(&delta_t)) {
        OutputDebugString((std::to_wstring(delta_t) + L"\n").c_str());
    };

    return 0;
};
int MainScene::Render() {

    Engine::IGraphic::SetStrokeWidth(10);
    Engine::IGraphic::DrawLine({ 50,50 }, { 200,100 });
    Engine::IGraphic::DrawRectangle({ 300,300 }, { 150,150 }, { 10,10 });


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
