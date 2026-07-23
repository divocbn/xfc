//
// Created by Divo on 23.07.2026.
//

#ifndef XFC_FILESYSTEM_H
#define XFC_FILESYSTEM_H

#include "xfc/numeric.h"

#include <filesystem>
#include <vector>

class xfFileSystem
{
public:
    [[nodiscard]]
    static bool Read(const std::filesystem::path& path, std::vector<u8>& data);

    [[nodiscard]]
    static bool Write(const std::filesystem::path& path, const std::vector<u8>& data);
};

#endif // XFC_FILESYSTEM_H
