#include <iostream>
#include "ChaosEngine/Device/Engine.h"
#include "Common.cpp"

using namespace std;

int main()
{
    std::cout << "Hello, world!" << std::endl;

    Chaos::Device::Engine engine;
    Chaos::Graphic::Renderer* renderer;
    // engine.createRenderer(&renderer);
    engine.createRenderer(nullptr);

    return 0;
}