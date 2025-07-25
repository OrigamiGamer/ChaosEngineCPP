// Game Example 1

#include <iostream>
#include "ChaosEngine.h"

using namespace std;
using namespace Chaos;

Chaos::Device::Engine engine;

namespace res {
    Chaos::shared_ptr<Graphic::Texture> tex_logo;
}

void GameInit();
bool GameExit();

int main()
{
    engine.initialize();
    engine.createDefaultDevice();

    Chaos::Device::EngineStartupProperty engineProp;
    engineProp.onGameInit = GameInit;
    engineProp.onGameExit = GameExit;
    engineProp.fps = 60;

    engine.start(&engineProp);
    engine.release();


    std::cout << "Hello, world!" << std::endl;
    return 0;
}

class Scene_MainPage : public Content::Scene {
public:
    Scene_MainPage() : Scene("MainScene") {}

    void onEnter()
    {
        std::cout << "entering scene: MainScene" << std::endl;
    }

    bool onExit()
    {
        std::cout << "exiting scene: MainScene" << std::endl;
        return true;
    }

    void update()
    {
        Graphic::RenderTask task;

        task.type = Graphic::RenderTaskType::Line;
        task.param = Graphic::RenderTaskParam_Line({ 100,100 }, { 300,300 }, 4.0);
        task.order = 0;
        ::engine.renderer->pushTask(task);

        task.type = Graphic::RenderTaskType::Texture;
        task.param = Graphic::RenderTaskParam_Texture({ 100,100 }, res::tex_logo.get());
        task.order = -1;
        ::engine.renderer->pushTask(task);





    }

} g_scene_mainPage;

void GameInit()
{
    res::tex_logo = ::engine.renderer->loadTextureFromImageFile(L"/res/origami_logo.png");

    Chaos::shared_ptr<Graphic::Viewport> viewport;
    Chaos::shared_ptr<Graphic::Viewport> viewport_2;

    if (::engine.renderer->createViewport(viewport)) {
        viewport->pos = { 10, 10 };
        viewport->size = { 500, 500 };
        viewport->viewPos = { 100, 100 };
        viewport->viewSize = { 500, 500 };
    }
    if (::engine.renderer->createViewport(viewport_2)) {
        viewport_2->pos = { 510, 10 };
        viewport_2->size = { 500, 500 };
        viewport_2->viewPos = { 200, 200 };
        viewport_2->viewSize = { 500, 500 };
    }   // NEW PROBLEM


    ::engine.stage->registerScene(g_scene_mainPage);
    ::engine.stage->switchScene("MainScene");

}

bool GameExit()
{
    return true;
}





/*

现在有一个GameEngine项目，一个直接引用了engine代码的GameDemo项目，它们现在都没有cmake文件，且GameDemo的项目位置位于engine根目录。
C++17，两者直接合并编译为exe文件。请给出这俩项目的cmake配置

（以上请问AI）

*/