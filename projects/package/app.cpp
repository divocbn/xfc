//
// Created by Divo on 23.07.2026.
//

#include "app.h"

#include "package.h"

#include "xfc/filesystem.h"
#include "xfc/log.h"

#include <cstdlib>
#include <exception>
#include <filesystem>
#include <format>
#include <string>
#include <string_view>
#include <vector>

struct xfPackageArgParsedOptions
{
    std::filesystem::path m_File;
    std::filesystem::path m_Output;

    bool m_List = false;
};

xfPackageArgParsedOptions options;

// TODO(module): later on move that somewhere into shared so i can reuse it across other projects
static bool xfParseArgs(const std::span<char*> args, std::string& error)
{
    for (size_t i = 1; i < args.size(); ++i)
    {
        const std::string_view arg = args[i];

        if (arg == "-l" || arg == "--list")
        {
            options.m_List = true;
        }
        else if (arg == "-o" || arg == "--out")
        {
            if (i + 1 >= args.size())
            {
                error = "missing output directory";
                return false;
            }

            options.m_Output = args[++i];
        }
        else if (arg.starts_with('-'))
        {
            error = std::format("unknown option: {}", arg);
            return false;
        }
        else if (options.m_File.empty())
        {
            options.m_File = arg;
        }
        else
        {
            error = std::format("unexpected argument: {}", arg);
            return false;
        }
    }

    if (options.m_File.empty())
    {
        error = "usage: package <file.cfxpackage> [-l|--list] [-o <dir>]";
        return false;
    }

    return true;
}

xfPackageApp::xfPackageApp(const s32 argc, char** argv) : xfApp("package", argc, argv)
{
}

s32 xfPackageApp::OnRun()
{
    std::string error;
    if (!xfParseArgs(m_Args, error))
    {
        XF_LOG_ERROR("{}", error);
        return EXIT_FAILURE;
    }

    std::vector<u8> data;
    if (!xfFileSystem::Read(options.m_File, data))
    {
        XF_LOG_ERROR("cannot read {}", options.m_File.string());
        return EXIT_FAILURE;
    }

    try
    {
        const xfPackage package(std::move(data));
        const auto& entries = package.GetEntries();

        XF_LOG_INFO("{}", options.m_File.filename().string());
        XF_LOG_INFO("entries : {}", entries.size());

        if (options.m_List)
        {
            for (size_t i = 0; i < entries.size(); ++i)
            {
                const xfPackageEntry& entry = entries[i];
                XF_LOG("{:>5}  {:08x}  {:>10}  {:>10}", i, entry.m_NameHash, entry.m_CompressedSize, entry.m_UncompressedSize);
            }
            return EXIT_SUCCESS;
        }

        const std::filesystem::path root = options.m_Output.empty() ?
            std::filesystem::path(options.m_File.stem().string() + "-extracted") :
            options.m_Output;

        for (const xfPackageEntry& entry : entries)
        {
            const std::string name = std::format("{:08x}", entry.m_NameHash);

            if (!xfFileSystem::Write(root / name, package.Decompress(entry)))
            {
                XF_LOG_ERROR("cannot write {}", (root / name).string());
                return EXIT_FAILURE;
            }
        }

        XF_LOG_INFO("extracted {} entries -> {}", entries.size(), root.string());

        return EXIT_SUCCESS;
    }
    catch (const std::exception& ex)
    {
        XF_LOG_ERROR("{}", ex.what());
        return EXIT_FAILURE;
    }
}
