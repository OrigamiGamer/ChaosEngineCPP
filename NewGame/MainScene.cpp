#pragma once
#include "MainScene.h"

namespace Global {
    Type::TextFormat default_textFormat;

}

MainScene::MainScene() {
    camera;
    timer;
    vec_image;
    text;
    image_bg;
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
    Manager::Texture.CreateTextureFromFile(locate(L"BG_FACE.png"), L"BG", &pTex);

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
    image_bg.size = { 1000,1000 };
    image_bg.SetTexture(Manager::Texture.GetTexture(L"BG"));

    RegComp(text);
    text.Init();
    text.size = { 1000, 300 };
    text.pos = { 50,100 };
    text.textFormat = Global::default_textFormat;

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



    struct StateList {
        BOOL last;
        BOOL current;
    };

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
        text.textFormat.SetContent(L"111");
        text.color = { D2D1::ColorF::HotPink, 1 };
    }
    else {
        state_update = FALSE;
        text.textFormat.SetContent(L"2222");
        text.color = { D2D1::ColorF::White, 1 };
    }

    Type::VirtualKeyState _VKS_W = WindowX::Prop::VirtKeyStateBuffer['W'];
    if (_VKS_W.current != _VKS_W.last) {
        _VKS_W.last = _VKS_W.current;

        if (_VKS_W.current == TRUE) {
            camera.viewPos.y -= 20;
        }
    }
    Type::VirtualKeyState _VKS_S = WindowX::Prop::VirtKeyStateBuffer['S'];
    if (_VKS_S.current != _VKS_S.last) {
        _VKS_S.last = _VKS_S.current;

        if (_VKS_S.current == TRUE) {
            camera.viewPos.y += 20;
        }
    }

    Type::VirtualKeyState _VKS_A = WindowX::Prop::VirtKeyStateBuffer['A'];
    if (_VKS_A.current != _VKS_A.last) {
        _VKS_A.last = _VKS_A.current;

        if (_VKS_A.current == TRUE) {
            camera.viewPos.x -= 20;
        }
    }
    Type::VirtualKeyState _VKS_D = WindowX::Prop::VirtKeyStateBuffer['D'];
    if (_VKS_D.current != _VKS_D.last) {
        _VKS_D.last = _VKS_D.current;

        if (_VKS_D.current == TRUE) {
            camera.viewPos.x += 20;
        }
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
