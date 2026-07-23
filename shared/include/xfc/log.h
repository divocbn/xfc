//
// Created by Divo on 23.07.2026.
//

#ifndef XFC_LOG_H
#define XFC_LOG_H

#include <fmt/color.h>
#include <fmt/format.h>

#include <string>
#include <string_view>
#include <utility>

inline static std::string s_LogAppName = "xfc";

template <typename... Args>
void xfLog(const fmt::text_style style, const std::string_view tag, fmt::format_string<Args...> format, Args&&... args)
{
    fmt::print(fmt::emphasis::bold, "[{}] ", s_LogAppName);
    fmt::print(style, "{}", tag);
    fmt::println(format, std::forward<Args>(args)...);
}

#define XF_LOG(...)         xfLog({}, "", __VA_ARGS__)
#define XF_LOG_INFO(...)    xfLog(fmt::fg(fmt::color::deep_sky_blue), "[info] ", __VA_ARGS__)
#define XF_LOG_WARN(...)    xfLog(fmt::fg(fmt::color::gold), "[warn] ", __VA_ARGS__)
#define XF_LOG_ERROR(...)   xfLog(fmt::fg(fmt::color::crimson), "[error] ", __VA_ARGS__)

#endif // XFC_LOG_H