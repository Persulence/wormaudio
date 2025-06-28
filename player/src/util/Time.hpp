#pragma once
#include <chrono>

namespace player
{
    using Seconds = double;
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock, Seconds>;
    using Sample = int;

    constexpr Sample NULL_SAMPLE = -1;

    struct Clock : std::chrono::steady_clock
    {
    };

    enum TimeType
    {
        IN_STATE,
        SINCE_EVENT_START
    };
}
