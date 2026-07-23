//
// Created by Divo on 23.07.2026.
//

#ifndef XFC_PTR_H
#define XFC_PTR_H

#include <memory>

template <typename T>
using xfPtr = std::unique_ptr<T>;

#endif // XFC_PTR_H
