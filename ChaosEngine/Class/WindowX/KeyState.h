#pragma once

#include "Class/WindowX/WindowX.h"



namespace Chaos::WindowX {



    struct KeyState {
    private:
        bool _last_pressed = false;
        bool _last_released = false;
    public:
        int virtualKey = VirtualKey::NONE;
        bool pressed = false;
        bool released = false;
        std::vector<Hotkey> hotkeys;

        friend class WindowX::Window;
    };



}