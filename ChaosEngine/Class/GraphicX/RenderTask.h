#pragma once

#include "Class/GraphicX/GraphicX.h"



namespace Chaos::GraphicX {



    struct RenderTask {
        RenderTaskType type = RenderTaskType::None;
        RenderTaskParam param;
        float order = 0.0f;

        RenderTask(RenderTaskType type = RenderTaskType::None, RenderTaskParam param = RenderTaskParam(), float order = 0.0f);
    };



}