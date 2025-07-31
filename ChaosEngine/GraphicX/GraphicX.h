#pragma once

#include "ChaosEngine.h"

namespace Chaos::GraphicX {



    class GraphicManager : public Base {
    public:
        // std::vector<GraphicX::Renderer*> renderers;

        GraphicManager();
        ~GraphicManager();

        // void registerRenderer(GraphicX::Renderer* new_renderer);
        // void registerRenderer(GraphicX::Renderer& new_renderer);

    };



    class Texture : public Resource {
    private:
        ID2D1Bitmap** _bitmap = nullptr;

        Texture(ID2D1Bitmap** new_bitmap);

    public:
        Texture();

        void release();

        vec2<float> getSize();

        friend class Renderer;

    };



    // Arguments of task types:



    // Line
    struct RenderTaskParam_Line {

        vec2<float> pos1{};
        vec2<float> pos2{};
        float strokeWidth = 1.0;

        RenderTaskParam_Line(
            vec2<float> pos1,
            vec2<float> pos2,
            float strokeWidth = 1.0
        );

    };



    // Texture
    struct RenderTaskParam_Texture {

        vec2<float> pos{};
        vec2<float> size{};
        Texture* texture = nullptr;
        float opacity = 1.0;
        vec2<float> pivot{};
        float rotation = 0.0;

        RenderTaskParam_Texture(
            vec2<float> pos,
            Texture* texture,
            vec2<float> size = { -1,-1 },
            vec2<float> pivot = { 0.0,0.0 },
            float rotation = 0.0
        );

    };



    struct RenderTask {

        RenderTaskType type = RenderTaskType::None;
        RenderTaskParam param;
        float order = 0.0;

        RenderTask(RenderTaskType type = RenderTaskType::None, RenderTaskParam param = RenderTaskParam(), float order = 0.0);

    };






    class Viewport : public Base {
    private:
        ID2D1Bitmap* _bitmap = nullptr;
    public:
        Renderer* renderer = nullptr;

        Chaos::vec2<float> pos;
        Chaos::vec2<float> size;
        Chaos::vec2<float> pivot;
        float rotation;

        Chaos::vec2<float> viewPos;
        Chaos::vec2<float> viewSize;

        Viewport(Renderer* new_renderer);

        void release();

        friend class Renderer;

    };



    class Renderer : public Device {
    private:
        ID2D1Factory* _d2dFactory = nullptr;
        IWICImagingFactory* _wicFactory = nullptr;
        IDWriteFactory* _dwriteFactory = nullptr;

        ID2D1HwndRenderTarget* _hwndRenderTarget = nullptr;

        ID2D1BitmapRenderTarget* _bitmapRenderTarget = nullptr;
        ID2D1SolidColorBrush* _brush = nullptr;

        std::map<std::string, Texture> _loadedTextures;

    public:
        std::vector<RenderTask> tasks;
        std::vector<GraphicX::Viewport*> viewports;

        Renderer();

        bool initialize(WindowX::Window* new_window);
        bool initialize(WindowX::Window& new_window);

        void release();

        bool createViewport(std::string viewportName = "", GraphicX::Viewport** out_viewport = nullptr);
        bool createViewport(GraphicX::Viewport*& out_viewport);

        Texture* loadTextureFromImageFile(std::wstring filename, std::string textureName = "");

        Texture* getLoadedTexture(std::string textureName);

        // Push a new task into the back of queue.
        void pushTask(RenderTask& new_task);

        // Pop the back task from the queue.
        void popTask();

    private:
        void render();

        friend class InternalDevice::Stage;

    };



}