#pragma once
#include "MainScene.h"

MainScene::MainScene() {
    MainScene::brush = NULL;
}

int MainScene::Init() {
    WindowX::pHwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGreen), &(MainScene::brush));

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
    //WindowX::pHwndRenderTarget->DrawRoundedRectangle({ {50,50,150,150},16,16 }, brush, 2);

    Engine::IGraphic::DrawLine({ 100,100 }, { 300,400 });

    OutputDebugStringA("render -> MainScene \n");

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
