#pragma once

#include "Class/WindowX/WindowX.h"



namespace Chaos::WindowX {



    // The state buffer of virtual keys. See enum VirtualKeyCode as index of this buffer.
    class KeyStateBuffer : public Resource {
    private:
        std::vector<KeyState> _keyStates;

    public:
        Window* window = nullptr;

        KeyStateBuffer();

        bool getKeyState(int virtualKey);

        bool addHotKey(int virtualKey, std::string name);

        // Remove a hot-key with target virtual key code and name.
        bool removeHotKey(int virtualKey, std::string name);

        // Clear all hot-keys of target virtual key code.
        // @param virtualKey The virtual key code of hot-keys to clear.
        bool clearHotKey(int virtualKey);

        // Clear all hot-keys with target name.
        // @param name The name of hot-keys to clear.
        // @return Return the count of hot-keys removed.
        int clearHotKey(std::string name);

        friend class WindowX::WindowManager;
        friend class WindowX::Window;
    };
    


}