//
// Created by Divo on 23.07.2026.
//

#ifndef XFC_TIMER_H
#define XFC_TIMER_H

#include <chrono>

using xfClock = std::chrono::high_resolution_clock;

class xfTimer
{
public:
    xfTimer();

    void Reset();

    [[nodiscard]]
    double GetElapsedTime() const;

private:
    std::chrono::time_point<xfClock> m_StartPoint;
};

#endif // XFC_TIMER_H
