#pragma once

#include "ChaosEngine.h"

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
        wchar_t _raw_path[MAX_PATH];
        GetModuleFileNameW(NULL, _raw_path, MAX_PATH);
        return std::wstring(_raw_path);
    }



    inline std::wstring getProgramFileDirectory()
    {
        return getFileDirectory(getProgramFilePath());
    }



    inline std::wstring getProgramFileName()
    {
        return getFileName(getProgramFilePath());
    }



    inline std::string formatFilePath(std::string filePath)
    {
        if (filePath.front() == L'/') filePath.erase(0, 1);
        std::replace(filePath.begin(), filePath.end(), L'/', L'\\');
        return filePath;
    }



    inline std::wstring formatFilePath(std::wstring filePath)
    {
        if (filePath.front() == L'/') filePath.erase(0, 1);
        std::replace(filePath.begin(), filePath.end(), L'/', L'\\');
        return filePath;
    }



    std::wstring locate(std::wstring filename)
    {
        if (filename.front() == L'/') filename.erase(0, 1);
        std::replace(filename.begin(), filename.end(), L'/', L'\\');
        return getProgramFileDirectory() + L"\\" + filename;
    }



    std::wstring getFileDirectory(std::wstring filePath)
    {
        filePath = formatFilePath(filePath);
        size_t pos_to_path = filePath.find_last_of(L'\\');
        return filePath.substr(0, pos_to_path);
    }



    std::string getFileDirectory(std::string filePath)
    {
        filePath = formatFilePath(filePath);
        size_t pos_to_path = filePath.find_last_of(L'\\');
        return filePath.substr(0, pos_to_path);
    }



    std::wstring getFileName(std::wstring filePath)
    {
        filePath = formatFilePath(filePath);
        size_t pos_to_path = filePath.find_last_of(L'\\');
        return filePath.substr(pos_to_path + 1, filePath.size() - pos_to_path - 1);
    }



    std::string getFileName(std::string filePath)
    {
        filePath = formatFilePath(filePath);
        size_t pos_to_path = filePath.find_last_of(L'\\');
        return filePath.substr(pos_to_path + 1, filePath.size() - pos_to_path - 1);
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



    inline std::string wstringToString(const std::wstring wstr)
    {
        int targetSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), NULL, 0, NULL, NULL);
        std::string str(targetSize, 0);
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), &str[0], targetSize, NULL, NULL);
        return str;
    }



    inline std::wstring stringToWstring(const std::string str)
    {
        int targetSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
        std::wstring wstr(targetSize, 0);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], targetSize);
        return wstr;
    }



}