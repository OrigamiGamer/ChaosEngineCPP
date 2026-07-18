#pragma once

#include "chaos/windows/windows.h"


namespace chaos::windows {



    struct KeyState {
    private:
        bool _last_pressed = false;
        bool _last_released = false;
    public:
        int keycode = keycode::NONE;
        bool pressed = false;
        bool released = false;
        std::vector<Hotkey> hotkeys;

        friend class windows::Window;
    };



}