#pragma once

#include "chaos/windows/windows.h"


namespace chaos::windows {



    class Window : public Base {
    private:
        GLFWwindow* _glfwWindow = nullptr;
        std::vector<KeyStateBuffer*> _keyStateBuffers;
        log::Logger _logger;

        void _onResized();

        void _onKey(int virtualKey);

    public:
        device::Stage* stage = nullptr;
        WindowStartupProperty startupProperty;
        vec2<int> pos;          // updated by callback
        vec2<int> size;         // updated by callback
        vec2<double> cursorPos; // updated by callback
        KeyStateBuffer keyStateBuffer;   // The state buffer of virtual keys. See enum VirtualKey as index of this buffer.

        Window();

        bool initialize(WindowStartupProperty* in_windowProp = nullptr);
        inline bool initialize(WindowStartupProperty& in_windowProp);

        void release();

        std::string getTitle();

        void setTitle(std::string in_title);

        void setSize(vec2<int> in_size);

        bool registerKeyStateBuffer(KeyStateBuffer* in_keyStateBuffer);

        bool unregisterKeyStateBuffer(KeyStateBuffer* in_keyStateBuffer);
        bool unregisterKeyStateBuffer(std::string keyStateBufferName);

        friend class windows::WindowManager;
        friend class graphics::Renderer;
        friend class device::Stage;
        friend class device::Engine;
    };



}