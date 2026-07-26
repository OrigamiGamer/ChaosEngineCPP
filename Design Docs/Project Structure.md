# ChaosEngine 项目结构

## 目录总览

```
ChaosEngineCPP/
├── CMakeLists.txt
├── CMakePresets.json
│
├── ChaosEngine/
│   ├── Engine/                             → 引擎核心
│   │   ├── Include/Chaos/                  →   PUBLIC 公开接口
│   │   │   ├── Chaos.h
│   │   │   ├── Core/Base.h
│   │   │   ├── Core/Vector.h
│   │   │   ├── Core/Color.h
│   │   │   ├── Core/System.h
│   │   │   ├── Graphics/IRenderer.h
│   │   │   ├── Graphics/IViewport.h
│   │   │   ├── Graphics/ITexture.h
│   │   │   ├── Graphics/RenderTask.h
│   │   │   ├── Graphics/RenderTaskParam.h
│   │   │   ├── Graphics/GraphicsServer.h
│   │   │   ├── Audio/IAudioEngine.h
│   │   │   └── Platform/IWindow.h
│   │   └── Source/Chaos/                   →   PRIVATE 引擎实现
│   │       ├── Chaos.cpp
│   │       ├── Core/Base.cpp
│   │       ├── Graphics/GraphicsServer.cpp
│   │       ├── Graphics/RenderTask.cpp
│   │       ├── Graphics/RenderTaskParam.cpp
│   │       ├── Platform/Window.cpp
│   │       └── Audio/
│   │
│   ├── Drivers/                            → PRIVATE 后端实现
│   │   ├── Include/                        →   Driver 头文件
│   │   │   ├── Audio/
│   │   │   │   ├── OpenAL/
│   │   │   │   │   ├── OpenAL.h
│   │   │   │   │   ├── AudioEngine.h
│   │   │   │   │   ├── AudioPlayer.h
│   │   │   │   │   ├── Buffer.h
│   │   │   │   │   └── Source.h
│   │   │   │   └── Other/
│   │   │   ├── Graphics/
│   │   │   │   ├── D2D/
│   │   │   │   │   ├── D2DRenderer.h
│   │   │   │   │   ├── D2DViewport.h
│   │   │   │   │   └── D2DTexture.h
│   │   │   │   └── Other/
│   │   │   └── Platform/
│   │   │       ├── Win32/
│   │   │       │   └── Win32Window.h
│   │   │       └── Other/
│   │   └── Source/                         →   Driver 实现
│   │       ├── Audio/
│   │       │   ├── OpenAL/
│   │       │   │   ├── OpenAL.cpp
│   │       │   │   ├── AudioEngine.cpp
│   │       │   │   ├── AudioPlayer.cpp
│   │       │   │   ├── Buffer.cpp
│   │       │   │   └── Source.cpp
│   │       │   └── Other/
│   │       ├── Graphics/
│   │       │   ├── D2D/
│   │       │   │   ├── D2DRenderer.cpp
│   │       │   │   ├── D2DViewport.cpp
│   │       │   │   └── D2DTexture.cpp
│   │       │   └── Other/
│   │       └── Platform/
│   │           ├── Win32/
│   │           │   └── Win32Window.cpp
│   │           └── Other/
│   │
│   └── Dependences/                        → 第三方依赖
│       ├── Include/
│       │   ├── al/                         → OpenAL 原始头文件
│       │   ├── glfw/                       → GLFW 头文件
│       │   └── sndfile/                    → libsndfile 头文件
│       ├── Lib/                            → .lib / .a 预编译库
│       └── Bin/                            → .dll 运行时库
│
├── Design Docs/
│   └── ProjectStructure.md
│
├── .gitignore
├── LICENSE.txt
└── README.md
```

## 三层架构

```
┌────────────────────────────────┐
│  ③ Engine Core                 │  引擎核心逻辑
│  Engine/Source/Chaos/           │  只依赖接口，不碰后端 API
└────────────┬───────────────────┘
             │  调用 IRenderer* / IAudioEngine*
┌────────────▼───────────────────┐
│  ② Abstraction Layer           │  纯虚接口 + 公共类型
│  Engine/Include/Chaos/          │  PUBLIC，对外可见
└────────────┬───────────────────┘
             │  实现 I* 接口
┌────────────▼───────────────────┐
│  ① Drivers                      │  底层 API 具体实现
│  Drivers/{Subsystem}/{Name}/    │  PRIVATE，对外不可见
└────────────────────────────────┘
```

| 层                  | 目录              | CMake 可见性 | 内容                                      |
| ------------------- | ----------------- | ------------ | ----------------------------------------- |
| ③ Engine Core       | `Engine/Source/`  | PRIVATE      | 引擎核心实现，不包含任何驱动头文件        |
| ② Abstraction Layer | `Engine/Include/` | PUBLIC       | 纯虚接口 + 公共类型，唯一对外暴露的头文件 |
| ① Drivers           | `Drivers/`        | PRIVATE      | 各子系统底层 API 封装，具体实现           |

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
    PUBLIC  ChaosEngine/Engine/Include
    PRIVATE
        ChaosEngine/Drivers/Include
        ChaosEngine/Dependences/Include
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

## 设计原则

### 1. 接口隔离

- `Engine/Include/Chaos/Graphics/IRenderer.h` 等为纯虚接口，不包含平台相关类型
- Drivers 中的头文件（如 `D2DRenderer.h`）通过 `PRIVATE` 保护，外部代码不可见
- Drivers 内部实现包含 `<d2d1.h>`、`<windows.h>` 等平台头文件，绝不泄露到上层

### 2. 编译期驱动选择

通过 `option()` + `if()` 控制编译哪些 Drivers。新增后端时只需在 `Drivers/{Subsystem}/{Name}/` 下添加实现，CMake 加一个 `if` 分支。未选中的驱动完全不参与编译。

### 3. 统一 Drivers 结构

```
Drivers/
├── Include/                      → 所有 Driver 头文件
│   ├── Audio/OpenAL/
│   ├── Graphics/D2D/
│   └── Platform/Win32/
└── Source/                       → 所有 Driver 实现
    ├── Audio/OpenAL/
    ├── Graphics/D2D/
    └── Platform/Win32/
```

和 `Engine/Include` + `Engine/Source` 结构一致。CMake 用一句 `Drivers/Include` 覆盖所有 Driver 头文件查找。

### 4. Dependences 分类

```
Dependences/
├── Lib/       .lib / .a 预编译库
├── Bin/       .dll 运行时库
└── Include/   第三方头文件（按库名分类）
    ├── al/       OpenAL
    ├── glfw/     GLFW
    └── sndfile/  libsndfile
```

D2D1.lib 属于 Windows SDK，由编译器自动处理。引擎封装的 OpenAL 代码放在 `Drivers/Source/Audio/OpenAL/`，不属于 Dependences。

## 目录结构约定

| 目录                    | CMake 可见性 | 用途                                  |
| ----------------------- | ------------ | ------------------------------------- |
| `Engine/Include/Chaos/` | `PUBLIC`     | 公开 API，`#include <Chaos/...>`      |
| `Engine/Source/Chaos/`  | `PRIVATE`    | 引擎核心实现                          |
| `Drivers/Include/`      | `PRIVATE`    | Driver 头文件，`#include <Audio/...>` |
| `Drivers/Source/`       | —            | Driver 实现文件                       |
| `Dependences/Include/`  | `PRIVATE`    | 第三方头文件                          |

## 命名规范

| 内容       | 规则                  | 示例                             |
| ---------- | --------------------- | -------------------------------- |
| 接口类     | `I` 前缀 + PascalCase | `IRenderer`, `IViewport`         |
| 引擎核心类 | PascalCase            | `GraphicsServer`, `RenderTask`   |
| Driver 类  | 后端名 + 接口名       | `D2DRenderer`, `D2DViewport`     |
| 命名空间   | `chaos`               | `namespace chaos { }`            |
| 文件名     | 与类名一致            | `IRenderer.h`, `D2DRenderer.cpp` |

## 接口设计

### Graphics

| 接口             | 关键方法                                                                              |
| ---------------- | ------------------------------------------------------------------------------------- |
| `IRenderer`      | `BeginDraw`, `EndDraw`, `Clear`, `DrawLine`, `DrawRect`, `DrawEllipse`, `DrawTexture` |
| `IViewport`      | `GetRect`, `SetRect`, `GetSize`                                                       |
| `ITexture`       | `GetSize`, `GetDPI`                                                                   |
| `GraphicsServer` | 单例，工厂方法 `CreateRenderer`，命令队列                                             |

### Audio

| 接口           | 关键方法                                          |
| -------------- | ------------------------------------------------- |
| `IAudioEngine` | `Play`, `Stop`, `Pause`, `SetVolume`, `LoadSound` |

### Platform

| 接口      | 关键方法                                         |
| --------- | ------------------------------------------------ |
| `IWindow` | `GetHandle`, `GetSize`, `PollEvents`, `SetTitle` |

## 未来扩展

新增渲染后端的步骤：

1. 在 `Drivers/Graphics/{Name}/` 下创建头文件和源文件
2. 实现 `IRenderer`、`IViewport`、`ITexture` 接口
3. 在 CMakeLists.txt 添加 `if(CHAOS_DRIVER_GRAPHICS STREQUAL "{Name}")`
4. 引擎核心代码零修改
