#pragma once

#include "chaos/graphics/graphics.h"


namespace chaos::graphics {



    struct RenderTask {
        RenderTaskType type = RenderTaskType::None;
        RenderTaskParam param;
        float order = 0.0f;

        RenderTask(RenderTaskType type = RenderTaskType::None, RenderTaskParam param = RenderTaskParam(), float order = 0.0f);
    };



}