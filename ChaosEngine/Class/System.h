#pragma once

#include "Class/Class.h"



namespace Chaos::System {

    // Release a COM object pointer safely.
    // 安全释放 COM 对象指针。
    template<typename T>
    void safeReleaseCOM(T*& pAny);

    // Get the current system time in microseconds.
    // 获取当前系统时间，以微秒为单位。
    unsigned long long getSystemTime();

    // Get the path of the current running program.
    // 获取当前运行程序的路径。
    std::string getProgramFilePath();
    std::wstring getProgramFilePathW();

    // Get the directory of the current running program.
    // 获取当前运行程序的目录。
    inline std::string getProgramFileDirectory();
    inline std::wstring getProgramFileDirectoryW();

    // Get the file name of the current running program.
    // 获取当前运行程序的文件名称。
    inline std::string getProgramFileName();
    inline std::wstring getProgramFileNameW();

    // Format a file path.
    // 格式化文件路径。
    inline std::string formatFilePath(std::string filePath);
    inline std::wstring formatFilePathW(std::wstring filePath);

    // Convert its relative path to absolute path.
    // 转换相对路径为绝对路径。
    std::string locate(std::string filename);
    std::wstring locateW(std::wstring filename);

    // Get the directory of a file.
    // 获取文件的目录。
    std::string getFileDirectory(std::string filePath);
    std::wstring getFileDirectoryW(std::wstring filePath);

    // Get the name of a file.
    // 获取文件的名称。
    std::string getFileName(std::string filePath);
    std::wstring getFileNameW(std::wstring filePath);

    // Convert a Unicode codepoint to UTF-8 string.
    // 将 Unicode 代码点转换为 UTF-8 字符串。
    std::string codepointToUtf8(uint32_t codepoint);

    // Convert a Unicode string to UTF-8 string.
    // 将 Unicode 字符串转换为 UTF-8 字符串。
    std::string wstringToString(const std::wstring wstr);

    // Convert a UTF-8 string to Unicode string.
    // 将 UTF-8 字符串转换为 Unicode 字符串。
    std::wstring stringToWstring(const std::string str);

}
