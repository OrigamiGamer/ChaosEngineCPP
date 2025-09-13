#pragma once

#include "Class/WindowX/WindowX.h"



namespace Chaos::WindowX {



    struct Hotkey {
        int virtualKey;
        std::string hotkeyName;
    public:
        Hotkey(int virtualKey, std::string hotkeyName);
    };
    


}