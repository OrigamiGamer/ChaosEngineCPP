#pragma once

#include "chaos/graphics/graphics.h"


namespace chaos::graphics {



    class Renderer : public Device {
    private:
        ID2D1Factory* _d2dFactory = nullptr;
        IWICImagingFactory* _wicFactory = nullptr;
        IDWriteFactory* _dwriteFactory = nullptr;

        ID2D1HwndRenderTarget* _hwndRenderTarget = nullptr;

        ID2D1BitmapRenderTarget* _bitmapRenderTarget = nullptr;
        ID2D1SolidColorBrush* _brush = nullptr;
        ID2D1SolidColorBrush* _fillBrush = nullptr;

    private:
        std::vector<Texture*> _loadedTextures;
        // std::vector<Canvas> _canvases;
        std::vector<RenderTask> _tasks;
        std::vector<D2D1_MATRIX_3X2_F> _transformMatrixHeap;

        log::Logger _logger;

    public:
        std::map<std::string, graphics::Viewport*> viewports;   // std::vector?

        Renderer();

        bool initialize(windows::Window* in_window);
        bool initialize(windows::Window& in_window);

        void release();

        // Load a texture resource from an image file, which can be gotten by a texture name.
        // 从图像文件加载一个纹理资源，可以通过纹理名称来获取它。
        // @param filename The path to an image file.
        // @param in_textureName The name of the texture loaded. If it's empty, it'll be the name of the image file excluding the path.
        Texture* loadTextureFromImageFile(std::string filename, std::string in_textureName = "");

        // Get the texture resource loaded by texture name.
        // 通过纹理名称获取已加载的纹理资源。
        Texture* getLoadedTexture(std::string textureName);

        bool registerViewport(graphics::Viewport* in_viewport, std::string viewportName = "");
        bool registerViewport(graphics::Viewport& in_viewport, std::string viewportName = "");

        // Graphics::Canvas* createCanvas(std::string in_canvasName = "");

        void SetCanvasSize(vec2<float> in_size);
        void SetCanvasSize(float x, float y);

        inline vec2<float> getCanvasSize() const;

        // Get maximum size of the canvas supported by this renderer.
        inline vec2<float> getMaximumCanvasSize() const;

        // Set the RGB color of the brush.
        // @param in_fillingBrushColor Unchange the color of the filling brush by default while any of RGB is "-1".
        void SetBrushColor(Color in_brushColor, Color in_fillingBrushColor = { -1,-1,-1 });

        // Push a new task into the back of queue.
        void pushTask(RenderTask& in_task);

        // Pop the back task from the queue.
        void popTask();

    private:
        void _pushTransform(vec2<float> pivot, float rotation, vec2<float> scale);
        void _popTransform();

        void _render();

        void _resizeWindow(vec2<int> in_size);

        friend class device::Stage;
        friend class windows::Window;
        friend class graphics::Canvas;
    };



}