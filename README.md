# ChaosEngine
`ChaosEngine`，中文译作`“混沌引擎”`，2D游戏引擎，将侧重于对GUI功能的设计，主要运行在Windows平台上。~~*未来将有可能支持跨平台(划掉)*~~


# 开发日志
### 正在进行不知道第多少次的项目重写计划...
### 本次重写将重点对项目结构的设计进行优化，以确保今后不再重写...pwp
### 详细请关注`Engine Desgin Docs`位置下的设计草稿~
### ——(2026.7.19)


# 第三方库

| 库 | 用途 | 文件 | 许可 |
|----|------|---------|------|
| [GLFW](https://www.glfw.org/) | 窗口创建、输入管理 | `glfw3.lib` | zlib/libpng |
| [OpenAL](https://openal.org/) | 3D 音频播放 | `OpenAL32.lib` + `OpenAL32.dll` | LGPL |
| [libsndfile](https://libsndfile.github.io/libsndfile/) | 音频文件解码 | `sndfile.lib` + `sndfile.dll` | LGPL |
| [Direct2D](https://learn.microsoft.com/en-us/windows/win32/direct2d/) | 2D 图形渲染（当前图形驱动） | Windows SDK，`D2D1.lib` | Windows SDK |