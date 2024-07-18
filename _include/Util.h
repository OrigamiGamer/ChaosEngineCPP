#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    template <class T>
    inline void SafeRelease(T** ppT)
    {
        if (*ppT) {
            (*ppT)->Release();
            *ppT = NULL;
        }
    }

    namespace Program {
        
        // Get the directory of this program.
        inline std::wstring root_path() {
            wchar_t _raw_path[MAX_PATH]; GetModuleFileName(NULL, _raw_path, MAX_PATH);
            return std::wstring(_raw_path);
        }

    }

    // Locate absolute filename from relative.
    std::wstring locate(std::wstring fileName) {
        std::wstring raw = Program::root_path();

        size_t lpos = raw.find_last_of('\\');
        size_t rpos = raw.find_last_of('e');  //  \folder\test.exe
        size_t _rpos = raw.size() - 1;

        std::wstring root;
        if (rpos + 1 == raw.size()) {
            root = raw.substr(0, lpos + 1);
        }
        else {
            root = raw + L"\\";
        }
        return std::wstring(root) + fileName;
    }

    namespace ColorMixer {

        static const UINT32 _redShift = 16;
        static const UINT32 _greenShift = 8;
        static const UINT32 _blueShift = 0;

        static const UINT32 _redMask = 0xff << _redShift;
        static const UINT32 _greenMask = 0xff << _greenShift;
        static const UINT32 _blueMask = 0xff << _blueShift;

        // r = static_cast<FLOAT>((rgb & _redMask) >> _redShift) / 255.f;
        // g = static_cast<FLOAT>((rgb & _greenMask) >> _greenShift) / 255.f;
        // b = static_cast<FLOAT>((rgb & _blueMask) >> _blueShift) / 255.f;

        inline FLOAT r(UINT32 rgb) {
            return static_cast<FLOAT>((rgb & _redMask) >> _redShift) / 255.f;
        }
        inline FLOAT g(UINT32 rgb) {
            return static_cast<FLOAT>((rgb & _greenMask) >> _greenShift) / 255.f;
        }
        inline FLOAT b(UINT32 rgb) {
            return static_cast<FLOAT>((rgb & _blueMask) >> _blueShift) / 255.f;
        }

    }

}
