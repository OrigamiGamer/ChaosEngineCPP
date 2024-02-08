#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    template <class T>
    inline void SafeRelease(T** ppT)
    {
        if (*ppT)
        {
            (*ppT)->Release();
            *ppT = NULL;
        }
    };

    namespace Program {
        inline std::wstring getRootPath() {
            wchar_t _raw_path[MAX_PATH]; GetModuleFileName(NULL, _raw_path, MAX_PATH);
            return std::wstring(_raw_path);
        };

    };

    // Locate absolute filename from relative
    std::wstring locate(std::wstring fileName) {
        std::wstring raw = Program::getRootPath();

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
    };

}
