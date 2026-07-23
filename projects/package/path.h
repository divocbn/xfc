//
// Created by Divo on 23.07.2026.
//

#ifndef XFC_PACKAGE_PATH_H
#define XFC_PACKAGE_PATH_H

#include "xfc/numeric.h"

#include <string>

std::string xfNormalizePath(const std::string& path);

u32 xfHashPath(const std::string& path);

#endif // XFC_PACKAGE_PATH_H
