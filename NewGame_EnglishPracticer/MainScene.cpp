#pragma once
#include "MainScene.h"

namespace Global {
    Type::TextFormat default_textFormat;
}

MainScene::MainScene() {

};
void MainScene::Init() {
    Global::default_textFormat.Init();

    // Load Resources
    Manager::Texture.CreateTextureFromFile(L"res/stonecutter.png", L"stone");
    Manager::Texture.CreateTextureFromFile(L"res/bg.png", L"bg");

    camera.Init();
    //camera.viewSize = { 300,300 };
    camera.viewPos = { 0,0 };
    this->SwitchCamera(camera); // 首先，场景不能没有镜头，所以至少要切换到一个镜头来让玩家眼前一亮（

    ease_x.Init(0, 0, Type::EASE_FUNC_INDEX_OUT, 5, 0.4);
    ease_y.Init(0, 0, Type::EASE_FUNC_INDEX_OUT, 5, 0.4);

    this->RegComp(image_bg);
    image_bg.size = WindowX::Prop::Size;
    image_bg.SetTexture(Manager::Texture.GetTexture(L"bg"));
    
    this->RegComp(image_player);
    image_player.size = { 200,200 };
    image_player.anchorPos = { image_player.size.width / 2, image_player.size.height / 2 };
    image_player.SetTexture(Manager::Texture.GetTexture(L"stone"));

    this->RegComp(text);
    text.pos = { 100,100 };
    text.size = { 300,300 };
    text.color.rgb = D2D1::ColorF::White;
    text.textFormat.SetContent(L"This is a text.");

};
void MainScene::Update() {
    if (VKBuffer.OnKeyDown('A')) {
        ease_x.SetNewValue(image_player.pos.x, image_player.pos.x - 100); // move left
        ease_x.Begin();
    }
    if (VKBuffer.OnKeyDown('D')) {
        ease_x.SetNewValue(image_player.pos.x, image_player.pos.x + 100); // move right
        ease_x.Begin();
    }
    if (VKBuffer.OnKeyDown('W')) {
        ease_y.SetNewValue(image_player.pos.y, image_player.pos.y - 100); // move up
        ease_y.Begin();
    }
    if (VKBuffer.OnKeyDown('S')) {
        ease_y.SetNewValue(image_player.pos.y, image_player.pos.y + 100); // move down
        ease_y.Begin();
    }

    ease_x.Update();
    ease_y.Update();
    image_player.pos.x = ease_x.GetSingleResult();
    image_player.pos.y = ease_y.GetSingleResult();
    camera.viewPos.x = -camera.viewSize.width / 2 + image_player.pos.x;
    camera.viewPos.y = -camera.viewSize.height / 2 + image_player.pos.y;

    text.textFormat.SetContent(to_wstring(image_player.pos.x) + L", " + to_wstring(image_player.pos.y));

};
void MainScene::Render() {

};
void MainScene::Release() {

};
int MainScene::OnSceneEntered() {

    return 0;
};
int MainScene::OnCameraEntered() {

    return 0;
};
bool MainScene::OnSceneExiting() {

    return true;
};
bool MainScene::OnCameraExiting() {

    return true;
};
