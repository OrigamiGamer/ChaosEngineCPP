#pragma once

#include "Class/WindowX/WindowX.h"



namespace Chaos::WindowX {



    KeyStateBuffer::KeyStateBuffer() :
        _keyStates(VirtualKey::LAST_VIRTUAL_KEY + 1)
    {
        this->INIT("KeyStateBuffer");

        // initialize virtual key list of this state buffer of keys
        for (size_t virtKey = VirtualKey::FIRST_VIRTUAL_KEY;virtKey < this->_keyStates.size();virtKey++) {
            this->_keyStates.at(virtKey).virtualKey = virtKey;
        }
    }



    bool KeyStateBuffer::getKeyState(int virtualKey)
    {
        if (virtualKey < VirtualKey::FIRST_VIRTUAL_KEY || virtualKey > VirtualKey::LAST_VIRTUAL_KEY) return false;

        return this->_keyStates.at(virtualKey).pressed;
    }



    bool KeyStateBuffer::addHotKey(int virtualKey, std::string hotkeyName)
    {
        if (virtualKey < VirtualKey::FIRST_VIRTUAL_KEY || virtualKey > VirtualKey::LAST_VIRTUAL_KEY) return false;

        if (hotkeyName.empty()) return false;

        auto& _hotkeys = this->_keyStates.at(virtualKey).hotkeys;
        for (auto it = _hotkeys.begin();it != _hotkeys.end();it++) {
            if ((*it).hotkeyName == hotkeyName) return false;   // the hot-key with this name has already existed
        }

        this->_keyStates.at(virtualKey).hotkeys.push_back(Hotkey(virtualKey, hotkeyName));
        return true;
    }



    bool KeyStateBuffer::removeHotKey(int virtualKey, std::string hotkeyName)
    {
        if (virtualKey < VirtualKey::FIRST_VIRTUAL_KEY || virtualKey > VirtualKey::LAST_VIRTUAL_KEY) return false;

        if (hotkeyName.empty()) return false;

        auto& _hotkeys = this->_keyStates.at(virtualKey).hotkeys;
        for (auto it = _hotkeys.begin();it != _hotkeys.end();it++) {
            if ((*it).hotkeyName == hotkeyName) {
                _hotkeys.erase(it);
                return true;
            }
        }
        return false;   // could NOT find this hot-key
    }



    bool KeyStateBuffer::clearHotKey(int virtualKey)
    {
        if (virtualKey < VirtualKey::FIRST_VIRTUAL_KEY || virtualKey > VirtualKey::LAST_VIRTUAL_KEY) return false;

        this->_keyStates[virtualKey].hotkeys.clear();
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