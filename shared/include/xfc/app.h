//
// Created by Divo on 23.07.2026.
//

#ifndef XFC_APP_H
#define XFC_APP_H

#include "xfc/numeric.h"

#include <span>
#include <string>
#include <string_view>

class xfApp
{
public:
    xfApp(std::string name, s32 argc, char** argv);
    virtual ~xfApp() = default;

    s32 Run();

protected:
    virtual s32 OnRun() = 0;

    [[nodiscard]]
    std::string_view GetName() const { return m_Name; }

    std::string m_Name;
    std::span<char*> m_Args;
};

#endif // XFC_APP_H
