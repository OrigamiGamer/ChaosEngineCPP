// Game Example 1

#include <iostream>
#include "Common.h"
#include "Common.cpp"

using namespace std;
using namespace Chaos;

Chaos::Device::Engine engine;

void GameInit();
bool GameExit();

int main()
{
    engine.initialize();
    engine.createDefaultDevice();

    Chaos::Device::EngineStartupProperty engineProp;
    engineProp.onGameInit = GameInit;
    engineProp.onGameExit = GameExit;
    engineProp.fps = 5;

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
        task.type = Graphic::RenderTaskTypes::Line;
        task.param = Graphic::RenderTaskParam_Line({ 100,100 }, { 300,300 }, 4.0);
        ::engine.renderer->pushTask(task);

        std::cout << "size of renderer tasks: " << ::engine.renderer->tasks.size() << std::endl;

    }

} g_scene_mainPage;

void GameInit()
{
    engine.stage->registerScene(g_scene_mainPage);
    engine.stage->switchScene("MainScene");
}

bool GameExit()
{
    return true;
}

