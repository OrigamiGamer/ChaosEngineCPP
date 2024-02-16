#pragma once
#include "MainScene.h"

namespace Global {
    Type::TextFormat default_textFormat;

}

MainScene::MainScene() {
    timer;
    vec_image;
    text;
};
void MainScene::Init() {
    Global::default_textFormat.Init();  // 还有一个空指针

    this->RegComp(timer);
    timer.Create(10000);
    timer.Begin();
    
    Type::Texture* lpTex = NULL;
    Manager::Texture.CreateTextureFromFile(locate(L"res\\texture\\stonecutter.png"), L"", &lpTex);

    /*size_t count = 100;
    vec_image.resize(count);
    for (size_t i = 0; i < count; i++) {
        ObjectList::Image& image = vec_image[i];
        this->RegComp(image);
        image.SetTexture(lpTex);
        image.size = { 30,30 };
        image.pos = { (float)(10.0 + rand() % 1400 + 1), (float)(10.0 + rand() % 900 + 1) };
        image.use_physics = true;
        image.mass = (double)(1000.0 + rand() % 100 + 1);
    };*/

    //RegComp(text);
    //text.Init();    // IntelliCode 炸了
};
void MainScene::Update() {
    /*if (GetKeyState('D') < 0) {
        Stage::SwitchScene(debug_scene);
    }*/

    ULONGLONG delta_t;
    if (timer.Todo(&delta_t)) {
        //timer.Pause();
        //image_2.vec_force.applied.clear();
        //OutputDebugString((std::to_wstring(GetTickCount()) + L"\n").c_str());
    };

};
void MainScene::Render() {

    //GraphicX::DrawRawText(L"ChaosEngine Text Demo", L"Microsoft YaHei", 64, { 1000,1000 }, { 50,50 });

    GraphicX::DrawRawText(L"test", Global::default_textFormat, { 100,100 });

};
void MainScene::Release() {



};
int MainScene::OnSceneEntered() {

    return 0;
};
bool MainScene::OnSceneExiting() {

    return true;
};
