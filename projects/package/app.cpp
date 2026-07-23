//
// Created by Divo on 23.07.2026.
//

#include "app.h"

#include "xfc/log.h"

xfPackageApp::xfPackageApp(const s32 argc, char** argv)
    : xfApp("package", argc, argv)
{

}

s32 xfPackageApp::OnRun()
{
    XF_LOG_INFO("xfPackageApp running");

    return EXIT_SUCCESS;
}
