# ChaosEngine 项目结构

## 目录总览

```
ChaosEngineCPP/
├── CMakeLists.txt
├── CMakePresets.json
│
├── ChaosEngine/
│   ├── Engine/                         → 引擎代码
│   │   ├── Include/                    →   PUBLIC
│   │   └── Source/                     →   PRIVATE
│   ├── Drivers/                        → 后端实现 (PRIVATE)
│   │   ├── Graphics/
│   │   │   ├── D2D/
│   │   │   └── Other/
│   │   └── Audio/
│   │       ├── OpenAL/
│   │       └── Other/
│   └── Dependences/                    → 第三方依赖
│       ├── Lib/
│       ├── Bin/
│       └── Include/
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
│  ③ Engine Core                 │  Engine 核心逻辑
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

| 层 | 目录 | CMake 可见性 | 内容 |
|----|------|-------------|------|
| ③ Engine Core | `Engine/Source/` | PRIVATE | 引擎核心实现，不包含任何驱动头文件 |
| ② Abstraction Layer | `Engine/Include/` | PUBLIC | 纯虚接口 + 公共类型，唯一对外暴露的头文件 |
| ① Drivers | `Drivers/` | PRIVATE | 各子系统底层 API 封装，具体实现 |

## 设计原则

### 1. 接口隔离

- `Engine/Include/Chaos/Graphics/IRenderer.h` 等为纯虚接口，不包含平台相关类型
- Drivers 中的头文件（如 `D2DRenderer.h`）通过 `PRIVATE` 保护，外部代码不可见
- Drivers 内部实现包含 `<d2d1.h>`、`<windows.h>` 等平台头文件，绝不泄露到上层

### 2. 编译期驱动选择

```cmake
option(CHAOS_DRIVER_AUDIO    "Audio driver"    "OpenAL")
option(CHAOS_DRIVER_GRAPHICS "Graphics driver" "D2D")
```

- 通过 `option()` + `if()` 控制编译哪些 Drivers
- 新增后端时只需在 `Drivers/{Subsystem}/{Name}/` 下添加实现，CMake 加一个 `if` 分支
- 未选中的驱动完全不参与编译

### 3. Drivers 内部结构

```
Drivers/
├── Graphics/
│   └── D2D/
│       ├── Include/         ← D2D 后端的私有头文件
│       └── Source/          ← D2D 后端实现
└── Audio/
    └── OpenAL/
        ├── Include/         ← OpenAL 后端的私有头文件
        └── Source/          ← OpenAL 后端实现
```

每个 Driver 独立管理自己的头文件和源文件，结构统一。

### 4. Dependences 分类

```
Dependences/
├── Lib/       ← .lib / .a 预编译库
├── Bin/       ← .dll 运行时库
└── Include/   ← 第三方头文件
```

- D2D1.lib 属于 Windows SDK，不放入 Dependences，由编译器自动处理
- 引擎封装的 OpenAL 代码放在 `Drivers/Audio/OpenAL/`，不属于 Dependences

## CMake 可见性策略

| 目录 | 可见性 | 效果 |
|------|--------|------|
| `Engine/Include/Chaos/` | `PUBLIC` | 链接 ChaosEngine 的目标可以 `#include <Chaos/...>` |
| `Engine/Source/Chaos/` | `PRIVATE` | 只有引擎内部能看到 |
| `Drivers/*/Include/` | `PRIVATE` | 只有对应 Driver 的源文件能看到 |
| `Dependences/Include/` | `PRIVATE` | 引擎内部使用，不对外泄露 |

## 命名规范

| 内容 | 规则 | 示例 |
|------|------|------|
| 接口类 | `I` 前缀 + PascalCase | `IRenderer`, `IViewport`, `ITexture` |
| 引擎核心类 | PascalCase | `GraphicsServer`, `RenderTask`, `Base` |
| Driver 类 | 后端名 + 接口名 | `D2DRenderer`, `D2DViewport` |
| 命名空间 | `chaos` | `namespace chaos { }` |
| 文件名 | 与类名一致 | `IRenderer.h`, `D2DRenderer.cpp` |

## 接口设计

### Graphics

| 接口 | 关键方法 |
|------|---------|
| `IRenderer` | `BeginDraw`, `EndDraw`, `Clear`, `DrawLine`, `DrawRect`, `DrawEllipse`, `DrawTexture` |
| `IViewport` | `GetRect`, `SetRect`, `GetSize` |
| `ITexture` | `GetSize`, `GetDPI` |
| `GraphicsServer` | 单例，工厂方法 `CreateRenderer`，命令队列 |

### Audio

| 接口 | 关键方法 |
|------|---------|
| `IAudioEngine` | `Play`, `Stop`, `Pause`, `SetVolume`, `LoadSound` |

### Platform

| 接口 | 关键方法 |
|------|---------|
| `IWindow` | `GetHandle`, `GetSize`, `PollEvents`, `SetTitle` |

## 未来扩展

新增渲染后端的步骤：

1. 在 `Drivers/Graphics/{Name}/` 下创建 `Include/` + `Source/`
2. 实现 `IRenderer`、`IViewport`、`ITexture` 接口
3. 在 CMakeLists.txt 添加 `if(CHAOS_DRIVER_GRAPHICS STREQUAL "{Name}")`
4. 引擎核心代码零修改
