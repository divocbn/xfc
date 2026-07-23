//
// Created by Divo on 23.07.2026.
//

#include "xfc/timer.h"

xfTimer::xfTimer()
{
    Reset();
}

void xfTimer::Reset()
{
    m_StartPoint = xfClock::now();
}

double xfTimer::GetElapsedTime() const
{
    return std::chrono::duration<double, std::milli>(xfClock::now() - m_StartPoint).count();
}
