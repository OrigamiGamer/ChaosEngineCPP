// Game Example 1

#include <iostream>
#include "Common.h"
#include "Common.cpp"

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
    res::tex_logo = ::engine.renderer->loadTextureFromFile(L"/res/origami_logo.png");

    // viewport 做到 renderer 里了
    // 接下来要让每个 Scene 都能拥有并访问一个 viewport

    Chaos::shared_ptr<Graphic::Viewport> viewport;
    if (::engine.renderer->createViewport(viewport)) {
        viewport->pos = { 10, 10 };
        viewport->size = { 500, 500 };
        viewport->viewPos = { 100, 100 };
        viewport->viewSize = { 500, 500 };
    }
    if (::engine.renderer->createViewport(viewport)) {
        viewport->pos = { 510, 10 };
        viewport->size = { 500, 500 };
        viewport->viewPos = { 200, 200 };
        viewport->viewSize = { 500, 500 };
    }   // NEW PROBLEM

    ::engine.stage->registerScene(g_scene_mainPage);
    ::engine.stage->switchScene("MainScene");

}

bool GameExit()
{
    return true;
}

