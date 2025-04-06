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

    engine.start(&engineProp);
    engine.release();


    std::cout << "Hello, world!" << std::endl;
    return 0;
}

void GameInit()
{

}

bool GameExit()
{
    return true;
}

class Scene_MainPage : public Content::Scene {
public:
    Scene_MainPage() : Scene("MainScene") {}



};