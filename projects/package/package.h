//
// Created by Divo on 23.07.2026.
//

#ifndef XFC_PACKAGE_PACKAGE_H
#define XFC_PACKAGE_PACKAGE_H

#include "xfc/numeric.h"

#include <string>
#include <vector>

struct xfPackageEntry // sizeof=0x10
{
    u32 m_NameHash;
    u32 m_RelOffset;
    u32 m_UncompressedSize;
    u32 m_CompressedSize;
};
static_assert(sizeof(xfPackageEntry) == 0x10);

struct xfPackageHeader // sizeof=0x08
{
    u32 m_Magic;
    u32 m_Flags;
};
static_assert(sizeof(xfPackageHeader) == 0x08);

class xfPackage
{
public:
    explicit xfPackage(std::vector<u8> data);

    [[nodiscard]]
    const std::vector<xfPackageEntry>& GetEntries() const
    {
        return m_Entries;
    }

    [[nodiscard]]
    std::vector<u8> Decompress(const xfPackageEntry& entry) const;

    [[nodiscard]]
    const xfPackageEntry* Find(const std::string& path) const;

private:
    void Parse();

    static constexpr u32 kMagic = 0x31584643; // CFX1

    std::vector<xfPackageEntry> m_Entries;
    std::vector<u8> m_Data;

    size_t m_DataStart = 0;
};

#endif // XFC_PACKAGE_PACKAGE_H
