#pragma once
#include "MainScene.h"

namespace Global {
    Type::TextFormat default_textFormat;

}

MainScene::MainScene() {
    timer;
    vec_image;
    text;
    image_bg;
};
void MainScene::Init() {
    Global::default_textFormat.Init();

    this->RegComp(timer);
    timer.Create(10000);
    timer.Begin();

    Type::Texture* pTex = NULL;
    Manager::Texture.CreateTextureFromFile(locate(L"res\\texture\\stonecutter.png"), L"stonecutter", &pTex);

    /*size_t count = 100;
    vec_image.resize(count);
    for (size_t i = 0; i < count; i++) {
        ObjectList::Image& image = vec_image[i];
        this->RegComp(image);
        image.SetTexture(pTex);
        image.size = { 30,30 };
        image.pos = { (float)(10.0 + rand() % 1400 + 1), (float)(10.0 + rand() % 900 + 1) };
        image.use_physics = true;
        image.mass = (double)(1000.0 + rand() % 100 + 1);
    };*/

    RegComp(text);
    text.Init();
    text.size = { 1000, 300 };
    text.pos = { 50,100 };
    text.textFormat = Global::default_textFormat;

    RegComp(image_bg);
    
    pTex = Manager::Texture.GetTexture(L"stonecutter");
    image_bg.SetTexture(pTex);

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



    static BOOL last_state_inside = FALSE;
    static BOOL state_inside = FALSE;
    static BOOL state_update = FALSE;

    state_inside = text.IsInside();

    // cheack update state
    if (last_state_inside != state_inside) { 
        last_state_inside = state_inside;
        state_update = TRUE;
    }

    // update event
    if (state_inside) {
        state_update = FALSE;
        text.textFormat.SetContent(L"我草，C++我爱死你了（");
        text.color = { D2D1::ColorF::HotPink, 1 };
    }
    else {
        state_update = FALSE;
        text.textFormat.SetContent(L"没事（");
        text.color = { D2D1::ColorF::White, 1 };
    }



};
void MainScene::Render() {


};
void MainScene::Release() {


};
int MainScene::OnSceneEntered() {

    return 0;
};
bool MainScene::OnSceneExiting() {

    return true;
};
