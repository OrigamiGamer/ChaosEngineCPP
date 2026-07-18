#pragma once

#include "chaos/chaos.h"


namespace chaos::system {

    // Release a COM object pointer safely.
    // 安全释放 COM 对象指针。
    template<typename T>
    void SafeReleaseCOM(T*& pAny);

    // Get the current system time in microseconds(μs).
    // Unit Conversion: 1μs = 10^(-3)ms = 10^(-6)s
    // 获取当前系统时间，以微秒为单位。
    // 单位转换：1微秒 = 10^(-3)毫秒 = 10^(-6)秒
    unsigned long long GetSystemTime();

    // Get the path of the current running program.
    // 获取当前运行程序的路径。
    std::string GetProgramFilePath();
    std::wstring GetProgramFilePathW();

    // Get the directory of the current running program.
    // 获取当前运行程序的目录。
    inline std::string GetProgramFileDirectory();
    inline std::wstring GetProgramFileDirectoryW();

    // Get the file name of the current running program.
    // 获取当前运行程序的文件名称。
    inline std::string GetProgramFileName();
    inline std::wstring GetProgramFileNameW();

    // Format a file path.
    // 格式化文件路径。
    inline std::string FormatFilePath(std::string filePath);
    inline std::wstring FormatFilePathW(std::wstring filePath);

    // Convert its relative path to absolute path.
    // 转换相对路径为绝对路径。
    std::string Locate(std::string filename);
    std::wstring LocateW(std::wstring filename);

    // Get the directory of a file.
    // 获取文件的目录。
    std::string GetFileDirectory(std::string filePath);
    std::wstring GetFileDirectoryW(std::wstring filePath);

    // Get the name of a file.
    // 获取文件的名称。
    std::string GetFileName(std::string filePath);
    std::wstring GetFileNameW(std::wstring filePath);

    // Convert a Unicode codepoint to UTF-8 string.
    // 将 Unicode 代码点转换为 UTF-8 字符串。
    std::string CodepointToUtf8(uint32_t codepoint);

    // Convert a Unicode string to UTF-8 string.
    // 将 Unicode 字符串转换为 UTF-8 字符串。
    std::string WstringToString(const std::wstring wstr);

    // Convert a UTF-8 string to Unicode string.
    // 将 UTF-8 字符串转换为 Unicode 字符串。
    std::wstring StringToWstring(const std::string str);

}
