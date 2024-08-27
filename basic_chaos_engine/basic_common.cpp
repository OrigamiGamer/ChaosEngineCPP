#pragma once

#include "basic_common.h"

namespace program {
#ifdef _WIN32
    inline std::wstring get_root_directory() {
        wchar_t _ch_dir[MAX_PATH];
        GetModuleFileNameW(NULL, _ch_dir, MAX_PATH);
        std::wstring dir(_ch_dir);
        return dir.erase(dir.find_last_of(L"\\") + 1, dir.size() - 1);
    }
#endif

    inline std::wstring locate(const std::wstring& filename) {
        if (filename.substr(0, 2) == L"./")
            return get_root_directory() + filename.substr(2, filename.size() - 2);
        return filename;
    }
}