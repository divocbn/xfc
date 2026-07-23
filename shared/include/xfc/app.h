//
// Created by Divo on 23.07.2026.
//

#ifndef XFC_APP_H
#define XFC_APP_H

#include "xfc/numeric.h"

#include <string>

class xfApp
{
public:
    xfApp(std::string name, s32 argc, char** argv);
    virtual ~xfApp() = default;

    s32 Run();

protected:
    virtual s32 OnRun() = 0;

    s32 GetArgCount() const;

    const char* GetArg(s32 index) const;

private:
    std::string m_Name;

    s32 m_ArgCount;
    char** m_Args;
};

#endif // XFC_APP_H
