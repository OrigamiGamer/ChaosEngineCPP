#pragma once
#include "MainScene.h"

MainScene::MainScene() {
    timer;
    pD2DBitmap = NULL;
};
int MainScene::Init() {
    this->RegComp(timer);
    timer.Create(100);
    timer.Begin();

    //TextureManager::CreateTextureFromFile(L"D:\\origami\\ChaosEngine\\ChaosEngineCPP\\NewGame\\res\\texture\\stonecutter.png");
    //TextureManager::Release();
    

    return 0;
};
int MainScene::Update() {

    if (GetKeyState('D') < 0) {
        Stage::SwitchScene(debug_scene);
    }

    ULONGLONG delta_t;
    if (timer.Todo(&delta_t)) {
        OutputDebugString((std::to_wstring(GetTickCount()) + L"\n").c_str());
    };

    return 0;
};
int MainScene::Render() {

    IGraphic::SetStrokeWidth(10);
    IGraphic::DrawLine({ 50,50 }, { 200,100 });
    IGraphic::DrawRectangle({ 300,300 }, { 150,150 }, { 10,10 });

    //WindowX::pHwndRenderTarget->DrawBitmap(pD2DBitmap);


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
