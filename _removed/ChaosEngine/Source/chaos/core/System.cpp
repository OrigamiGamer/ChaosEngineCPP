#include "chaos/chaos.h"


namespace chaos::system {



    template<typename T = IUnknown>
    void SafeReleaseCOM(T*& pAny)
    {
        if (pAny != nullptr) {
            pAny->Release();    // decrease reference count
            pAny = nullptr;
        }
    }



    inline unsigned long long GetSystemTime()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count();
    }



    inline std::string GetProgramFilePath()
    {
        char _raw_path[MAX_PATH];
        GetModuleFileNameA(NULL, _raw_path, MAX_PATH);
        return std::string(_raw_path);
    }



    inline std::wstring GetProgramFilePathW()
    {
        wchar_t _raw_path[MAX_PATH];
        GetModuleFileNameW(NULL, _raw_path, MAX_PATH);
        return std::wstring(_raw_path);
    }



    inline std::string GetProgramFileDirectory()
    {
        return GetFileDirectory(GetProgramFilePath());
    }



    inline std::wstring GetProgramFileDirectoryW()
    {
        return GetFileDirectoryW(GetProgramFilePathW());
    }



    inline std::string GetProgramFileName()
    {
        return GetFileName(GetProgramFilePath());
    }



    inline std::wstring GetProgramFileNameW()
    {
        return GetFileNameW(GetProgramFilePathW());
    }



    inline std::string FormatFilePath(std::string filePath)
    {
        if (filePath.front() == '/') filePath.erase(0, 1);
        std::replace(filePath.begin(), filePath.end(), '/', '\\');
        return filePath;
    }



    inline std::wstring FormatFilePathW(std::wstring filePath)
    {
        if (filePath.front() == L'/') filePath.erase(0, 1);
        std::replace(filePath.begin(), filePath.end(), L'/', L'\\');
        return filePath;
    }



    std::string Locate(std::string filename)
    {
        if (filename.front() == '/') filename.erase(0, 1);
        std::replace(filename.begin(), filename.end(), '/', '\\');
        return GetProgramFileDirectory() + "\\" + filename;
    }



    std::wstring LocateW(std::wstring filename)
    {
        if (filename.front() == L'/') filename.erase(0, 1);
        std::replace(filename.begin(), filename.end(), L'/', L'\\');
        return GetProgramFileDirectoryW() + L"\\" + filename;
    }



    std::wstring GetFileDirectoryW(std::wstring filePath)
    {
        filePath = FormatFilePathW(filePath);
        size_t pos_to_path = filePath.find_last_of(L'\\');
        return filePath.substr(0, pos_to_path);
    }



    std::string GetFileDirectory(std::string filePath)
    {
        filePath = FormatFilePath(filePath);
        size_t pos_to_path = filePath.find_last_of('\\');
        return filePath.substr(0, pos_to_path);
    }



    std::wstring GetFileNameW(std::wstring filePath)
    {
        filePath = FormatFilePathW(filePath);
        size_t pos_to_path = filePath.find_last_of(L'\\');
        return filePath.substr(pos_to_path + 1, filePath.size() - pos_to_path - 1);
    }



    std::string GetFileName(std::string filePath)
    {
        filePath = FormatFilePath(filePath);
        size_t pos_to_path = filePath.find_last_of(L'\\');
        return filePath.substr(pos_to_path + 1, filePath.size() - pos_to_path - 1);
    }



    std::string CodepointToUtf8(uint32_t codepoint)
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



    inline std::string WstringToString(const std::wstring wstr)
    {
        int targetSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), NULL, 0, NULL, NULL);
        std::string str(targetSize, 0);
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), &str[0], targetSize, NULL, NULL);
        return str;
    }



    inline std::wstring StringToWstring(const std::string str)
    {
        int targetSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
        std::wstring wstr(targetSize, 0);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], targetSize);
        return wstr;
    }



}