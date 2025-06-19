#pragma once
#include <chrono>

namespace player
{
    using Clock = std::chrono::steady_clock;
    using Seconds = std::chrono::duration<double>;

    enum TimeType
    {
        IN_STATE,
        SINCE_EVENT_START
    };
}
