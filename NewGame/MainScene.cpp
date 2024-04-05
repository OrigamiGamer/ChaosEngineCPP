#pragma once
#include "MainScene.h"

namespace Global {
    Type::TextFormat default_textFormat;

}

MainScene::MainScene() {
    camera;
    vk_state_buffer;
    timer;
    vec_image;
    text;
    image_bg;
    ease;
};
void MainScene::Init() {
    Global::default_textFormat.Init();

    camera.viewSize = { 300,300 };
    camera.viewPos = { 0,0 };
    this->SwitchCamera(camera);

    this->RegComp(timer);
    timer.Create(10000);
    timer.Begin();

    Type::Texture* pTex = NULL;
    Manager::Texture.CreateTextureFromFile(locate(L"res/tex/bg.png"), L"bg", &pTex);

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


    RegComp(image_bg);
    image_bg.size = { 200,200 };
    image_bg.SetTexture(Manager::Texture.GetTexture(L"bg"));

    RegComp(text);
    text.Init();
    text.size = { 1000, 300 };
    text.pos = { 50,100 };
    text.textFormat = Global::default_textFormat;

    RegComp(ease);
    ease.Init(camera.viewPos.x, camera.viewPos.x, Type::EASE_FUNC_INDEX_INOUT, 3, 0.5);
    

};
void MainScene::Update() {
    ULONGLONG delta_t;
    if (timer.Todo(&delta_t)) {
        //timer.Pause();
        //image_2.vec_force.applied.clear();
        //OutputDebugString((std::to_wstring(GetTickCount()) + L"\n").c_str());
    };

    text.textFormat.SetContent(std::to_wstring(camera.viewPos.x) + L", " + std::to_wstring(camera.viewPos.y));

    static BOOL last_state_inside = FALSE;
    static BOOL state_inside = FALSE;
    static BOOL state_update = FALSE;

    state_inside = text.OnHover();

    // cheack update state
    if (last_state_inside != state_inside) {
        last_state_inside = state_inside;
        state_update = TRUE;
    }

    // update event
    if (state_inside) {
        state_update = FALSE;
        //text.textFormat.SetContent(L"111");
        text.color = { D2D1::ColorF::HotPink, 1 };
    }
    else {
        state_update = FALSE;
        //text.textFormat.SetContent(L"2222");
        text.color = { D2D1::ColorF::White, 1 };
    }

    if (vk_state_buffer.GetState('W')) camera.viewPos.y -= 10;
    if (vk_state_buffer.GetState('S')) camera.viewPos.y += 10;
    if (vk_state_buffer.GetState('A')) camera.viewPos.x -= 10;
    if (vk_state_buffer.GetState('D') && ease.state == false) {
        ease.SetNewValue(camera.viewPos.x, camera.viewPos.x + 100);
        ease.Begin();
    }

    if (ease.state) camera.viewPos.x = ease.GetSingleResult();

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