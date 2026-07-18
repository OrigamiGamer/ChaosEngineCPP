#include "chaos/windows/windows.h"


namespace chaos::windows {



    KeyStateBuffer::KeyStateBuffer() :
        _keyStates(keycode::LAST_KEYCODE + 1)
    {
        this->INIT("KeyStateBuffer");

        // initialize virtual key list of this state buffer of keys
        for (int virtKey = keycode::FIRST_KEYCODE;virtKey < this->_keyStates.size();virtKey++) {
            this->_keyStates.at(virtKey).keycode = virtKey;
        }
    }



    bool KeyStateBuffer::getKeyState(int keycode)
    {
        if (keycode < keycode::FIRST_KEYCODE || keycode > keycode::LAST_KEYCODE) return false;
        return this->_keyStates.at(keycode).pressed;
    }



    bool KeyStateBuffer::addHotKey(int keycode, std::string hotkeyName)
    {
        if (keycode < keycode::FIRST_KEYCODE || keycode > keycode::LAST_KEYCODE) return false;
        if (hotkeyName.empty()) return false;

        auto& _hotkeys = this->_keyStates.at(keycode).hotkeys;
        for (auto it = _hotkeys.begin();it != _hotkeys.end();it++) {
            if ((*it).hotkeyName == hotkeyName) return false;   // the hot-key with this name has already existed
        }

        this->_keyStates.at(keycode).hotkeys.push_back(Hotkey(keycode, hotkeyName));
        return true;
    }



    bool KeyStateBuffer::removeHotKey(int keycode, std::string hotkeyName)
    {
        if (keycode < keycode::FIRST_KEYCODE || keycode > keycode::LAST_KEYCODE) return false;
        if (hotkeyName.empty()) return false;

        auto& _hotkeys = this->_keyStates.at(keycode).hotkeys;
        for (auto it = _hotkeys.begin();it != _hotkeys.end();it++) {
            if ((*it).hotkeyName == hotkeyName) {
                _hotkeys.erase(it);
                return true;
            }
        }
        return false;   // could NOT find this hot-key
    }



    bool KeyStateBuffer::clearHotKey(int keycode)
    {
        if (keycode < keycode::FIRST_KEYCODE || keycode > keycode::LAST_KEYCODE) return false;

        this->_keyStates[keycode].hotkeys.clear();
        return false;
    }



    int KeyStateBuffer::clearHotKey(std::string hotkeyName)
    {
        if (hotkeyName.empty()) return 0;

        int _count = 0;
        for (auto& keyState : this->_keyStates) {
            for (auto it = keyState.hotkeys.begin();it != keyState.hotkeys.end();it++) {
                if ((*it).hotkeyName == hotkeyName) {
                    keyState.hotkeys.erase(it);
                    it--;
                    _count++;
                };
            }
        }
        return _count;
    }



}