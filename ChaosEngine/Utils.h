#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    template <class T>
    void SafeRelease(T** ppT)
    {
        if (*ppT)
        {
            (*ppT)->Release();
            *ppT = NULL;
        }
    };

    // Locate absolute filename from relative
    std::wstring locate(std::wstring fileName) {
        wchar_t _path[MAX_PATH];
        GetModuleFileName(NULL, _path, MAX_PATH);
        std::wstring path = std::wstring(_path);
        size_t pos_close = path.find_last_of('\\');
        size_t pos_e = path.find_last_of('e');  //  \folder\test.exe
        std::wstring header_path;
        if (pos_e + 1 == path.size()) {
            header_path = path.substr(0, pos_close + 1);
        }
        else {
            header_path = path + L"\\";
        }
        return std::wstring(header_path) + fileName;
    };

}
