#pragma once

#include "Class/GraphicX/GraphicX.h"



namespace Chaos::GraphicX {



    class Renderer : public Device {
    private:
        ID2D1Factory* _d2dFactory = nullptr;
        IWICImagingFactory* _wicFactory = nullptr;
        IDWriteFactory* _dwriteFactory = nullptr;

        ID2D1HwndRenderTarget* _hwndRenderTarget = nullptr;

        ID2D1BitmapRenderTarget* _bitmapRenderTarget = nullptr;
        ID2D1SolidColorBrush* _brush = nullptr;

    private:
        std::vector<Texture*> _loadedTextures;
        std::vector<RenderTask> _tasks;
        std::vector<D2D1_MATRIX_3X2_F> _transformMatrixes;

    public:
        std::map<std::string, GraphicX::Viewport*> viewports;

        Renderer();

        bool initialize(WindowX::Window* new_window);
        bool initialize(WindowX::Window& new_window);

        void release();

        // Load a texture resource from an image file, which can be gotten by a texture name.
        // 从图像文件加载一个纹理资源，可以通过纹理名称来获取它。
        // @param filename The path to an image file.
        // @param new_textureName The name of the texture loaded. If it's empty, it'll be the name of the image file excluding the path.
        Texture* loadTextureFromImageFile(std::string filename, std::string new_textureName = "");

        // Get the texture resource loaded by texture name.
        // 通过纹理名称获取已加载的纹理资源。
        Texture* getLoadedTexture(std::string textureName);

        bool registerViewport(GraphicX::Viewport* new_viewport, std::string viewportName = "");
        bool registerViewport(GraphicX::Viewport& new_viewport, std::string viewportName = "");

        void SetCanvasSize(vec2<float> new_size);
        void SetCanvasSize(float x, float y);

        inline vec2<float> getCanvasSize() const;

        // Get maximum size of the canvas supported by this renderer.
        inline vec2<float> getMaximumCanvasSize() const;

        // Push a new task into the back of queue.
        void pushTask(RenderTask& new_task);

        // Pop the back task from the queue.
        void popTask();

    private:
        void _pushTransform(vec2<float> pivot, float rotation, vec2<float> scale);
        void _popTransform();

        void _render();

        void _resizeWindow(vec2<int> new_size);

        friend class InternalDevice::Stage;
        friend class WindowX::Window;

    };



}