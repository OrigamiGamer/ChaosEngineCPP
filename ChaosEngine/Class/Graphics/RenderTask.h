#pragma once

#include "Class/Graphics/Graphics.h"



namespace Chaos::Graphics {



    struct RenderTask {
        RenderTaskType type = RenderTaskType::None;
        RenderTaskParam param;
        float order = 0.0f;

        RenderTask(RenderTaskType type = RenderTaskType::None, RenderTaskParam param = RenderTaskParam(), float order = 0.0f);
    };



}