//
// Created by Divo on 23.07.2026.
//

#include "xfc/app.h"
#include "xfc/log.h"
#include "xfc/timer.h"

xfApp::xfApp(std::string name, const s32 argc, char** argv)
    : m_Name(std::move(name))
    , m_ArgCount(argc)
    , m_Args(argv)
{
    s_LogAppName = m_Name;
}

s32 xfApp::Run()
{
    XF_LOG("starting...");

    const xfTimer timer;

    const s32 result = OnRun();

    XF_LOG("finished in {:.3f} ms", timer.GetElapsedTime());

    return result;
}

s32 xfApp::GetArgCount() const
{
    return m_ArgCount;
}

const char* xfApp::GetArg(const s32 index) const
{
    if (index < 0 || index >= m_ArgCount)
    {
        return nullptr;
    }

    return m_Args[index];
}
