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

    inline std::wstring getProgramFilePath()
    {
        wchar_t _raw_path[MAX_PATH]; GetModuleFileNameW(NULL, _raw_path, MAX_PATH);
        return std::wstring(_raw_path);
    }

    inline std::wstring getProgramFileDirectory()
    {
        std::wstring programPath = getProgramFilePath();
        size_t pos_to_path = programPath.find_last_of(L'\\');
        return programPath.substr(0, pos_to_path);
    }

    inline std::wstring getProgramFileName()
    {
        std::wstring programPath = getProgramFilePath();
        size_t pos_to_path = programPath.find_last_of(L'\\');
        return programPath.substr(pos_to_path + 1, programPath.size() - pos_to_path - 1);
    }

    std::wstring locate(std::wstring filename)
    {
        if (filename.front() == L'/') filename.erase(0, 1);
        std::replace(filename.begin(), filename.end(), L'/', L'\\');
        return getProgramFileDirectory() + L"\\" + filename;
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