//
// Created by Divo on 23.07.2026.
//

#include "xfc/app.h"
#include "xfc/log.h"
#include "xfc/timer.h"

#ifdef _WIN32
#include <windows.h>

static void xfEnableConsoleColors()
{
    const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD mode = 0;
    if (output != INVALID_HANDLE_VALUE && GetConsoleMode(output, &mode))
    {
        SetConsoleMode(output, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
}
#endif

xfApp::xfApp(std::string name, const s32 argc, char** argv)
    : m_Name(std::move(name))
    , m_Args(argv, argc)
{
#ifdef _WIN32
    xfEnableConsoleColors();
#endif
}

s32 xfApp::Run()
{
    XF_LOG("starting...");

    const xfTimer timer;

    const s32 result = OnRun();

    XF_LOG("finished in {:.3f} ms", timer.GetElapsedTime());

    return result;
}
