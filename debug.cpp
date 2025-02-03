#include <iostream>
#include "Common.h"
#include "Common.cpp"

using namespace std;

int main()
{
    Chaos::Device::Engine engine;
    engine.createRenderer();


    std::cout << "Hello, world!" << std::endl;
    return 0;
}