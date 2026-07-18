#pragma once

#include "chaos/windows/windows.h"

namespace chaos::windows {


    /**
     * @brief The state buffer of virtual keys. See enum `Keycode` as index of this buffer.
     */
    class KeyStateBuffer : public Resource {
    private:
        std::vector<KeyState> _keyStates;

    public:
        Window* window = nullptr;

    public:
        KeyStateBuffer();

        bool getKeyState(int keycode);

        bool addHotKey(int keycode, std::string hotkeyName);

        /**
         * @brief Remove a hot-key with target virtual key code and name.
         *
         * @param keycode The key code.
         * @param name The name of hot-key.
         * @return `true`
         * @return `false`
         */
        bool removeHotKey(int keycode, std::string hotkeyName);

        /**
         * @brief Clear all hot-keys of target virtual key code.
         *
         * @param keycode The key code of hot-keys to clear.
         * @return `true`
         * @return `false`
         */
        bool clearHotKey(int keycode);

        /**
         * @brief Clear all hot-keys with target name.
         *
         * @param name The name of hot-keys.
         * @return `int` Return the count of removed hot-keys.
         */
        int clearHotKey(std::string hotkeyName);


        friend class windows::WindowManager;
        friend class windows::Window;
    };


}