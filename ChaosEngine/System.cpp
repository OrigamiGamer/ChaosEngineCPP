#pragma once

#include "Common.h"

namespace Chaos::System {

    template<typename T = IUnknown>
    void safeReleaseCOM(T*& pAny)
    {
        if (pAny != nullptr) {
            pAny->Release();
            pAny = nullptr;
        }
    }

    inline unsigned long long getSystemTime()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count();
    }

    inline std::wstring getProgramPath()
    {
        wchar_t _raw_path[MAX_PATH]; GetModuleFileNameW(NULL, _raw_path, MAX_PATH);
        return std::wstring(_raw_path);
    }

    std::wstring locate(std::wstring fileName)
    {
        std::wstring raw = getProgramPath();

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

    std::string codepointToUtf8(uint32_t codepoint)
    {
        std::wstring wideCharString;
        wideCharString.push_back(static_cast<wchar_t>(codepoint));

        int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wideCharString.c_str(), -1, NULL, 0, NULL, NULL);
        if (utf8Length == 0) {
            return "";
        }

        std::vector<char> utf8String(utf8Length);
        WideCharToMultiByte(CP_UTF8, 0, wideCharString.c_str(), -1, utf8String.data(), utf8Length, NULL, NULL);
        utf8String.pop_back(); // remove char NULL

        return std::string(utf8String.begin(), utf8String.end());
    }

}