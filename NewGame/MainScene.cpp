#pragma once
#include "MainScene.h"

// MainScene::brush = new ;

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
    // WindowX::pHwndRenderTarget->DrawRoundedRectangle({ {50,50,150,150},16,16 }, );

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
