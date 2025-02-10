#include <iostream>
#include "Common.h"
#include "Common.cpp"

using namespace std;

int main()
{
    Chaos::Device::Engine engine;
    engine.initialize();
    std::cout << engine.GET_TOP_TYPE() << std::endl;
    // engine.createDefaultDevice();

    Chaos::shared_ptr<Chaos::Device::Window> window;
    engine.createWindow(&window);
    window->initialize();
    
    



    engine.release();

    std::cout << "Hello, world!" << std::endl;
    return 0;
}