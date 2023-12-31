#pragma once
#include "MainScene.h"

MainScene::MainScene() {
    timer;
    image;
    
};
void MainScene::Init() {
    this->RegComp(timer);
    timer.Create(100);
    timer.Begin();

    this->RegComp(image);
    Type::Texture* lpTex = NULL;
    Manager::Texture.CreateTextureFromFile(locate(L"res\\texture\\stonecutter.png"), L"", &lpTex);
    image.SetTexture(lpTex);
    image.size = { 100, 100 };
    image.pos = { 200, 200 };

};
void MainScene::Update() {

    if (GetKeyState('D') < 0) {
        Stage::SwitchScene(debug_scene);
    }

    ULONGLONG delta_t;
    if (timer.Todo(&delta_t)) {
        //OutputDebugString((std::to_wstring(GetTickCount()) + L"\n").c_str());
    };

};
void MainScene::Render() {

    IGraphic::SetStrokeWidth(10);
    IGraphic::DrawLine({ 50,50 }, { 200,100 });
    IGraphic::DrawRectangle({ 300,300 }, { 150,150 }, { 10,10 });

};
void MainScene::Release() {



};
int MainScene::OnSceneEntered() {

    return 0;
};
bool MainScene::OnSceneExiting() {

    return true;
};
