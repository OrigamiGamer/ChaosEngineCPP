#include <iostream>
#include "Common.h"
#include "Common.cpp"

using namespace std;

typedef void (*WindowPosFunc)(Chaos::Device::Window* window, Chaos::vec2<int> pos);
typedef void(*WindowSizeFunc)(Chaos::Device::Window* window, Chaos::vec2<int> size);
typedef void(*WindowFocusFunc)(Chaos::Device::Window* window, bool focused);
typedef void(*WindowMaximizeFunc)(Chaos::Device::Window* window, bool maximized);
typedef void(*WindowCloseFunc)(Chaos::Device::Window* window);


void callbackWindowPos(GLFWwindow* window, int xpos, int ypos);
void callbackWindowClose(GLFWwindow* window);
void callbackWindowSize(GLFWwindow* window, int width, int height);
void callbackWindowFocus(GLFWwindow* window, int focused);
void callbackWindowMaximize(GLFWwindow* window, int maximized);

GLFWwindowiconifyfun;
GLFWwindowrefreshfun;
GLFWwindowcontentscalefun;


Chaos::Device::Engine engine;

int main()
{
    engine.initialize();
    // engine.createDefaultDevice();
    engine.createWindow();

    glfwSetWindowPosCallback(engine.window->_glfwWindow, callbackWindowPos);
    glfwSetWindowCloseCallback(engine.window->_glfwWindow, callbackWindowClose);

    engine.start();
    // engine.stop();

    engine.release();


    std::cout << "Hello, world!" << std::endl;
    return 0;
}

void callbackWindowPos(GLFWwindow* window, int xpos, int ypos)
{
    std::cout << xpos << ", " << ypos << std::endl;
    engine.stop();
}

void callbackWindowClose(GLFWwindow* window)
{
    std::cout << "The window is closed." << std::endl;
}
