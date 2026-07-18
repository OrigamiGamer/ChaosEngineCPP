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
        std::vector<RenderTask> _tasks;
        std::vector<D2D1_MATRIX_3X2_F> _transformMatrixHeap;

        log::Logger _logger;

    public:
        std::map<std::string, graphics::Viewport*> viewports;   // std::vector?

        Renderer();

        bool initialize(windows::Window* in_mainWindow);
        bool initialize(windows::Window& in_mainWindow);

        bool registerSubWindow(windows::Window* in_subWindow);
        bool registerSubWindow(windows::Window& in_subWindow);

        bool unregisterSubWindow(windows::Window* in_subWindow);
        bool unregisterSubWindow(windows::Window& in_subWindow);

        void release();

        /**
         * @brief Load a texture resource from an image file.
         * @param filename The path to an image file.
         * @param in_textureName The name of the texture loaded. If empty, uses the image filename.
         * @return `nullptr`: the texture had already been loaded.
         */
        Texture* loadTextureFromImageFile(std::string filename, std::string in_textureName = "");

        /**
         * @brief Get the texture resource loaded by texture name.
         * @param textureName Name of the texture.
         */
        Texture* getLoadedTexture(std::string textureName);

        bool registerViewport(graphics::Viewport* in_viewport, std::string viewportName = "");
        bool registerViewport(graphics::Viewport& in_viewport, std::string viewportName = "");

        void SetCanvasSize(vec2<float> in_size);
        void SetCanvasSize(float x, float y);

        inline vec2<float> getCanvasSize() const;

        /** @brief Get maximum size of the canvas supported by this renderer. */
        inline vec2<float> getMaximumCanvasSize() const;

        /**
         * @brief Set the color of the brush.
         * @param in_brushColor RGB color.
         */
        void SetBrushColor(Color in_brushColor);
        void SetFillBrushColor(Color in_fillBrushColor);

        /**
         * @brief Push a task into the back of render queue.
         * @param in_task new render task.
         */
        void pushTask(RenderTask& in_task);

        /**
         * @brief Pop the back task from the render queue.
         */
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