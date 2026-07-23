//
// Created by Divo on 23.07.2026.
//

#include "package.h"

#include "path.h"

#include <lz4.h>

#include <cstring>
#include <stdexcept>

xfPackage::xfPackage(std::vector<u8> data) : m_Data(std::move(data))
{
    Parse();
}

void xfPackage::Parse()
{
    if (m_Data.size() < sizeof(xfPackageHeader))
    {
        throw std::runtime_error("package smaller than header size");
    }

    xfPackageHeader header{};
    std::memcpy(&header, m_Data.data(), sizeof(header));

    if (header.m_Magic != kMagic)
    {
        throw std::runtime_error("invalid package magic, not a cfxpackage??");
    }

    size_t countOffset = sizeof(xfPackageHeader);

    if ((header.m_Flags & 1u) != 0)
    {
        const u32 unkLength = header.m_Flags >> 1 & 0x1FFF;

        if (unkLength != 0)
        {
            countOffset += unkLength;
        }
    }

    if (countOffset > m_Data.size() || sizeof(u32) > m_Data.size() - countOffset)
    {
        throw std::runtime_error("package too small for header");
    }

    u32 count = 0;
    std::memcpy(&count, m_Data.data() + countOffset, sizeof(count));

    const size_t entriesOffset = countOffset + sizeof(count);

    m_DataStart = entriesOffset + count * sizeof(xfPackageEntry);
    if (m_DataStart > m_Data.size())
    {
        throw std::runtime_error("package too small for package entry headers");
    }

    m_Entries.reserve(count);

    for (u32 i = 0; i < count; ++i)
    {
        xfPackageEntry entry;
        std::memcpy(&entry, m_Data.data() + entriesOffset + i * sizeof(xfPackageEntry), sizeof(xfPackageEntry));

        m_Entries.push_back(entry);
    }
}

std::vector<u8> xfPackage::Decompress(const xfPackageEntry& entry) const
{
    const size_t offset = m_DataStart + entry.m_RelOffset;

    if (offset > m_Data.size() || entry.m_CompressedSize > m_Data.size() - offset)
    {
        throw std::runtime_error("entry payload out of bounds");
    }

    std::vector<u8> out(entry.m_UncompressedSize);

    const s32 compressedSize = static_cast<s32>(entry.m_CompressedSize);
    const s32 uncompressedSize = static_cast<s32>(entry.m_UncompressedSize);

    LZ4_decompress_safe((char*)m_Data.data() + offset, (char*)out.data(), compressedSize, uncompressedSize);

    return out;
}

const xfPackageEntry* xfPackage::Find(const std::string& path) const
{
    const u32 hash = xfHashPath(path);

    for (const xfPackageEntry& entry : m_Entries)
    {
        if (entry.m_NameHash == hash)
        {
            return &entry;
        }
    }

    return nullptr;
}
