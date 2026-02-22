#pragma once

#include "Class/WindowX/WindowX.h"



namespace Chaos::WindowX {



    struct WindowStartupProperty {
        vec2<int> size = { 800, 600 };

        // If the value of a coordinate is -1, the position will be the center of primary monitor in that single coordinate.
        // 如果一个坐标轴的数值为 -1，那么在该坐标轴上，窗口位置将为初始显示器的中心。
        vec2<int> pos = { -1, -1 };

        std::string title = "Window";

        Callback_WindowClose onWindowClose = nullptr;
    };



}