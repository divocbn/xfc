//
// Created by Divo on 23.07.2026.
//

#ifndef XFC_PACKAGE_APP_H
#define XFC_PACKAGE_APP_H

#include "xfc/app.h"

class xfPackageApp final : public xfApp
{
public:
    xfPackageApp(s32 argc, char** argv);

protected:
    s32 OnRun() override;
};

#endif // XFC_PACKAGE_APP_H
