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

    this->RegObject(image);
    Type::Texture* lpTex = NULL;
    Manager::Texture.CreateTextureFromFile(locate(L"res\\texture\\stonecutter.png"), L"", &lpTex);
    image.SetTexture(lpTex);
    image.size = { 50, 50 };
    image.pos = { 200, 200 };
    image.use_physics = TRUE;
    image.mass = 1;
    image.AddForce(FORCE(15*10, 0));

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

    GraphicX::SetStrokeWidth(10);
    GraphicX::DrawLine({ 50,50 }, { 200,100 });
    GraphicX::DrawRectangle({ 300,300 }, { 150,150 }, { 10,10 });

};
void MainScene::Release() {



};
int MainScene::OnSceneEntered() {

    return 0;
};
bool MainScene::OnSceneExiting() {

    return true;
};
