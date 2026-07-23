//
// Created by Divo on 23.07.2026.
//

#include "path.h"

#include <fnv1a32.h>

#include <algorithm>
#include <filesystem>

std::string xfNormalizePath(const std::string& path)
{
    std::string normalized = path;
    std::ranges::replace(normalized, '\\', '/');

    normalized = std::filesystem::path(normalized).lexically_normal().generic_string();

    std::ranges::transform(normalized, normalized.begin(), [](const unsigned char c)
    {
        return static_cast<char>(std::tolower(c));
    });

    return normalized;
}

u32 xfHashPath(const std::string& path) // 0x6E7A70
{
    const std::string normalized = xfNormalizePath(path);
    return fnv1a32_str(normalized);
}
