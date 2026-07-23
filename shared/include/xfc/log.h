//
// Created by Divo on 23.07.2026.
//

#ifndef XFC_LOG_H
#define XFC_LOG_H

#include <fmt/color.h>
#include <fmt/format.h>

#include <string_view>
#include <utility>

template <typename... Args>
void xfLog(const std::string_view app, const fmt::text_style style, const std::string_view tag, fmt::format_string<Args...> format, Args&&... args)
{
    fmt::print(fmt::emphasis::bold, "[{}] ", app);
    fmt::print(style, "{}", tag);
    fmt::println(format, std::forward<Args>(args)...);
}

#define XF_LOG(...)       xfLog(GetName(), {}, "", __VA_ARGS__)
#define XF_LOG_INFO(...)  xfLog(GetName(), fmt::fg(fmt::color::deep_sky_blue), "[info] ", __VA_ARGS__)
#define XF_LOG_WARN(...)  xfLog(GetName(), fmt::fg(fmt::color::gold), "[warn] ", __VA_ARGS__)
#define XF_LOG_ERROR(...) xfLog(GetName(), fmt::fg(fmt::color::crimson), "[error] ", __VA_ARGS__)

#endif // XFC_LOG_H
