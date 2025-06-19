#pragma once
#include <chrono>

namespace player
{
    using Seconds = std::chrono::duration<double>;

    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

    struct Clock : std::chrono::steady_clock
    {
    };

    enum TimeType
    {
        IN_STATE,
        SINCE_EVENT_START
    };
}
