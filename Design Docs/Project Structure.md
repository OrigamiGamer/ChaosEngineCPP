# ChaosEngine 项目结构

## 目录总览

```
ChaosEngineCPP/
├── CMakeLists.txt
├── CMakePresets.json
│
├── ChaosEngine/
│   ├── Engine/                              → ②③ 引擎公开接口 + 核心实现
│   │   ├── Include/                         → ② 抽象层（公开 API，PUBLIC）
│   │   │   ├── Chaos.h                      → 统一入口
│   │   │   ├── Core/Base.h                  → 引擎基类
│   │   │   └── Audio/                       → 音频抽象接口
│   │   │       ├── IAudioEngine.h
│   │   │       └── IAudioPlayer.h
│   │   └── Source/                          → ③ 引擎核心实现（PRIVATE）
│   │       └── Core/
│   │           └── Base.cpp
│   │
│   ├── Drivers/                             → ① 后端实现（PRIVATE）
│   │   ├── Include/                         → 所有 Driver 头文件
│   │   │   ├── Audio/
│   │   │   │   └── OpenAL/                  → OpenAL 音频后端
│   │   │   │       ├── AudioEngine.h
│   │   │   │       ├── AudioPlayer.h
│   │   │   │       ├── Buffer.h
│   │   │   │       ├── Source.h
│   │   │   │       └── OpenAL.h             → 聚合引用
│   │   │   ├── Graphics/
│   │   │   │   └── D2D/                     → D2D 图形后端
│   │   │   │       └── D2D.h
│   │   │   └── Platform/
│   │   │       └── Win32/                   → Win32 平台后端
│   │   │           └── Win32.h
│   │   └── Source/                          → 所有 Driver 实现
│   │       ├── Audio/
│   │       │   └── OpenAL/
│   │       │       ├── AudioEngine.cpp
│   │       │       ├── AudioPlayer.cpp
│   │       │       ├── Buffer.cpp
│   │       │       └── Source.cpp
│   │       ├── Graphics/
│   │       │   └── D2D/
│   │       │       └── D2D.cpp
│   │       └── Platform/
│   │           └── Win32/
│   │               └── Win32.cpp
│   │
│   └── Dependences/                         → 第三方依赖
│       ├── Include/
│       │   ├── al/           OpenAL 原始 API
│       │   ├── glfw/         GLFW 窗口库
│       │   └── sndfile/      libsndfile 音频解码
│       ├── Lib/              预编译 .lib / .a
│       └── Bin/              运行时 .dll
│
├── Design Docs/
│   ├── CMake Guide.md
│   ├── Markdown Guide.md
│   └── Project Structure.md
│
├── .gitignore
├── LICENSE.txt
└── README.md
```

## 三层架构

```
┌───────────────────────────────────┐
│  ③ Engine Core                    │  引擎核心逻辑
│  Engine/Source/                    │  只依赖接口，不碰后端 API
└───────────┬───────────────────────┘
            │  IAudioEngine*, IRenderer*
┌───────────▼───────────────────────┐
│  ② Abstraction Layer              │  纯虚接口 + 公共类型
│  Engine/Include/                   │  公开 API
└───────────┬───────────────────────┘
            │  实现 I* 接口
┌───────────▼───────────────────────┐
│  ① Drivers                        │  底层 API 具体实现
│  Drivers/{Subsystem}/{Name}/       │  内部实现，对外不可见
└───────────────────────────────────┘
```

| 层                  | 目录              | 内容                                      |
| ------------------- | ----------------- | ----------------------------------------- |
| ③ Engine Core       | `Engine/Source/`  | 引擎核心实现，不包含任何驱动头文件        |
| ② Abstraction Layer | `Engine/Include/` | 纯虚接口 + 公共类型，唯一对外暴露的头文件 |
| ① Drivers           | `Drivers/`        | 各子系统底层 API 封装，具体实现           |

## CMake

```cmake
cmake_minimum_required(VERSION 3.10)
project(ChaosEngine VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)


###### Driver Options ######

option(CHAOS_DRIVER_AUDIO    "Audio driver"    "OpenAL")
option(CHAOS_DRIVER_GRAPHICS "Graphics driver" "D2D")
option(CHAOS_DRIVER_PLATFORM "Platform driver" "Win32")


###### ChaosEngine ######

add_library(ChaosEngine STATIC)
set_target_properties(ChaosEngine PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

target_include_directories(ChaosEngine
    PUBLIC ChaosEngine
)

target_sources(ChaosEngine PRIVATE
    ChaosEngine/Engine/Source/Core/Base.cpp
)

link_directories(ChaosEngine/Dependences/Lib)


###### Audio ######

if(CHAOS_DRIVER_AUDIO STREQUAL "OpenAL")
    target_sources(ChaosEngine PRIVATE
        ChaosEngine/Drivers/Source/Audio/OpenAL/AudioEngine.cpp
        ChaosEngine/Drivers/Source/Audio/OpenAL/AudioPlayer.cpp
        ChaosEngine/Drivers/Source/Audio/OpenAL/Buffer.cpp
        ChaosEngine/Drivers/Source/Audio/OpenAL/Source.cpp
    )
    target_link_libraries(ChaosEngine PRIVATE
        OpenAL32.lib
        sndfile.lib
    )
endif()


###### Graphics ######

if(CHAOS_DRIVER_GRAPHICS STREQUAL "D2D")
    target_sources(ChaosEngine PRIVATE
        ChaosEngine/Drivers/Source/Graphics/D2D/D2D.cpp
    )
    target_link_libraries(ChaosEngine PRIVATE
        D2D1.lib
    )
endif()


###### Platform ######

if(CHAOS_DRIVER_PLATFORM STREQUAL "Win32")
    target_sources(ChaosEngine PRIVATE
        ChaosEngine/Drivers/Source/Platform/Win32/Win32.cpp
    )
    target_link_libraries(ChaosEngine PRIVATE
        glfw3.lib
    )
endif()
```

## `#include` 约定

所有 `#include` 从项目根 `ChaosEngine/` 开始写，和磁盘路径一致：

```cpp
// 引擎公开 API
#include "Engine/Include/Core/Base.h"
#include "Engine/Include/Audio/IAudioEngine.h"

// 驱动内部代码
#include "Drivers/Include/Audio/OpenAL/AudioEngine.h"
#include "Drivers/Include/Audio/OpenAL/AudioPlayer.h"

// 第三方库
#include "Dependences/Include/al/alc.h"
#include "Dependences/Include/al/al.h"
#include "Dependences/Include/glfw/glfw3.h"
#include "Dependences/Include/sndfile/sndfile.h"
```

| 来源             | `#include` 前缀             | 示例                                           |
| ---------------- | --------------------------- | ---------------------------------------------- |
| Engine 公开 API  | `"Engine/Include/..."`      | `"Engine/Include/Core/Base.h"`                 |
| Drivers 内部代码 | `"Drivers/Include/..."`     | `"Drivers/Include/Audio/OpenAL/AudioEngine.h"` |
| 第三方库         | `"Dependences/Include/..."` | `"Dependences/Include/al/alc.h"`               |

## 设计原则

### 1. 接口隔离

- `Engine/Include/Audio/IAudioEngine.h` 等为纯虚接口，不包含平台相关类型
- Drivers 中 `.h` 用前向声明代替底层 include（如 `struct ALCdevice;`），底层头文件只在 `.cpp` 中出现
- 第三方库头文件统一放在 `Dependences/Include/` 下，保持原始目录名

### 2. 编译期驱动选择

通过 `option()` + `if()` 控制编译哪些 Drivers。新增后端时只需在 `Drivers/{Subsystem}/{Name}/` 下添加实现，CMake 加一个 `if` 分支。

### 3. 一致性

```
Engine/              Drivers/             Dependences/
├── Include/         ├── Include/         ├── Include/
└── Source/          └── Source/          ├── Lib/
                                          └── Bin/
```

三个一级目录内部结构一致，`Include/` 放头文件，`Source/` 放实现文件。

### 4. 命名空间

```
接口：    chaos::audio::IAudioEngine
驱动：    chaos::audio::openal::AudioEngine
接口：    chaos::graphics::IRenderer
驱动：    chaos::graphics::d2d::Renderer
```

去掉冗余的 `drivers` 层，接口在子系统命名空间下，驱动在后端名子命名空间下。

## 命名规范

| 内容       | 规则                  | 示例                                     |
| ---------- | --------------------- | ---------------------------------------- |
| 接口类     | `I` 前缀 + PascalCase | `IRenderer`, `IViewport`, `IAudioEngine` |
| 引擎核心类 | PascalCase            | `GraphicsServer`, `RenderTask`, `Base`   |
| Driver 类  | 后端名 + 接口名       | `D2DRenderer`, `D2DViewport`             |
| 命名空间   | `chaos::子系统::后端` | `chaos::audio::openal`                   |
| 文件名     | 与类名一致            | `IAudioEngine.h`, `AudioEngine.cpp`      |

## 接口设计

### Graphics

| 接口             | 关键方法                                                                              |
| ---------------- | ------------------------------------------------------------------------------------- |
| `IRenderer`      | `BeginDraw`, `EndDraw`, `Clear`, `DrawLine`, `DrawRect`, `DrawEllipse`, `DrawTexture` |
| `IViewport`      | `GetRect`, `SetRect`, `GetSize`                                                       |
| `ITexture`       | `GetSize`, `GetDPI`                                                                   |
| `GraphicsServer` | 单例，工厂方法 `CreateRenderer`，命令队列                                             |

### Audio

| 接口           | 关键方法                                                       |
| -------------- | -------------------------------------------------------------- |
| `IAudioEngine` | `Initialize`, `Shutdown`, `CreateAudioPlayer`                  |
| `IAudioPlayer` | `LoadAudio`, `Play`, `Pause`, `Stop`, `SetVolume`, `GetVolume` |

### Platform

| 接口      | 关键方法                                         |
| --------- | ------------------------------------------------ |
| `IWindow` | `GetHandle`, `GetSize`, `PollEvents`, `SetTitle` |

## 未来扩展

新增渲染后端的步骤：

1. 在 `Drivers/Graphics/{Name}/` 下创建头文件和源文件
2. 实现 `IRenderer`、`IViewport`、`ITexture` 接口
3. 在 CMakeLists.txt 添加 `if(CHAOS_DRIVER_GRAPHICS STREQUAL "{Name}")` 分支
4. 引擎核心代码零修改
