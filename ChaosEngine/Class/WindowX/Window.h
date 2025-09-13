#pragma once

#include "Class/WindowX/WindowX.h"



namespace Chaos::WindowX {



    class Window : public Base {
    private:
        GLFWwindow* _glfwWindow = nullptr;
        std::vector<KeyStateBuffer*> _keyStateBuffers;

        void _onResized();

        void _onKey(int virtualKey);

    public:
        InternalDevice::Stage* stage = nullptr;
        WindowProperty initialProperty;
        vec2<int> pos;          // updated by callback
        vec2<int> size;         // updated by callback
        vec2<double> cursorPos; // updated by callback
        KeyStateBuffer keyStateBuffer;   // The state buffer of virtual keys. See enum VirtualKey as index of this buffer.

        Window();

        bool initialize(WindowProperty* new_windowProp = nullptr);
        bool initialize(WindowProperty& new_windowProp);

        void release();

        std::string getTitle();

        void setTitle(std::string new_title);

        void setSize(vec2<int> new_size);

        bool registerKeyStateBuffer(KeyStateBuffer* new_keyStateBuffer);

        bool unregisterKeyStateBuffer(KeyStateBuffer* new_keyStateBuffer);
        bool unregisterKeyStateBuffer(std::string keyStateBufferName);

        friend class WindowX::WindowManager;
        friend class GraphicX::Renderer;
        friend class InternalDevice::Stage;
        friend class InternalDevice::Engine;
    };



}