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

    struct Tempo
    {
    public:
        int numerator{4};
        int denominator{4};
        double bpm{120};

        Seconds barsToSeconds(const double bars) const
        {
            // :4 is treated as a reference
            double base = static_cast<double>(denominator) / 4;

            return beatsToSeconds(base);
        }

        Seconds beatsToSeconds(const double beats) const
        {
            double base = static_cast<double>(denominator) / 4;

            return beats / (bpm / 60) / base;
        }

    private:
    };
}
