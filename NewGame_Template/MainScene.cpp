#pragma once
#include "MainScene.h"

namespace Global {
    Type::TextFormat default_textFormat;
}

MainScene::MainScene() {

};
void MainScene::Init() {
    Global::default_textFormat.Init();

    camera.viewSize = { 300,300 };
    camera.viewPos = { 0,0 };
    this->SwitchCamera(camera);


};
void MainScene::Update() {

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