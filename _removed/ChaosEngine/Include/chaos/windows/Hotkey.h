#pragma once

#include "chaos/windows/windows.h"


namespace chaos::windows {



    struct Hotkey {
        int keycode;
        std::string hotkeyName;
    public:
        Hotkey(int keycode, std::string hotkeyName);
    };
    


}