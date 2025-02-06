#include <iostream>
#include "Common.h"
#include "Common.cpp"

using namespace std;

int main()
{
    Chaos::Device::Engine engine;
    engine.createRenderer();
    engine.createWindow();
    engine.release();

    std::cout << "Hello, world!" << std::endl;
    return 0;
}