//
// Created by Divo on 23.07.2026.
//

#include "xfc/filesystem.h"

#include <fstream>

bool xfFileSystem::Read(const std::filesystem::path& path, std::vector<u8>& data)
{
    std::ifstream stream(path, std::ios::binary | std::ios::ate);
    if (!stream)
    {
        return false;
    }

    const std::streamsize size = stream.tellg();
    if (size < 0)
    {
        return false;
    }

    data.resize(static_cast<size_t>(size));
    stream.seekg(0, std::ios::beg);

    if (!stream.read(reinterpret_cast<char*>(data.data()), size))
    {
        data.clear();
        return false;
    }

    return true;
}

bool xfFileSystem::Write(const std::filesystem::path& path, const std::vector<u8>& data)
{
    if (path.has_parent_path())
    {
        std::error_code error;
        std::filesystem::create_directories(path.parent_path(), error);

        if (error)
            return false;
    }

    std::ofstream stream(path, std::ios::binary);
    if (!stream)
        return false;

    if (data.empty())
        return false;

    stream.write((char*)data.data(), (std::streamsize)data.size());

    return stream.good();
}
