#include <iostream>
#include "Common.h"
#include "Common.cpp"

using namespace std;

Chaos::Device::Engine engine;

int main()
{
    engine.initialize();
    engine.createDefaultDevice();
    // engine.createWindow();

    engine.start();
    // engine.stop();

    engine.release();


    std::cout << "Hello, world!" << std::endl;
    return 0;
}
