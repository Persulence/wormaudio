#pragma once
#include <chrono>

#include "Data.hpp"

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

    struct TimeSignature
    {
        int numerator{4};
        int denominator{4};

        INTERNAL_SERIALIZE
        {
            using namespace cereal;
            ar(make_nvp("numerator", numerator));
            ar(make_nvp("denominator", denominator));
        }
    };

    struct Tempo
    {
        util::Data<TimeSignature> timeSig;
        util::Data<double> bpm{120};

        Tempo() = default;

        [[nodiscard]] Seconds barsToSeconds(const double bars) const
        {
            return beatsToSeconds(bars * timeSig.getValue().numerator);
        }

        [[nodiscard]] Seconds beatsToSeconds(const double beats) const
        {
            // :4 is treated as a reference
            const double base = static_cast<double>(timeSig.getValue().denominator) / 4;

            return beats / (*bpm / 60) / base;
        }

        util::Data<TimeSignature> getTimeSig() const
        {
            return timeSig;
        }

        INTERNAL_SERIALIZE
        {
            using namespace cereal;
            ar(make_nvp("timeSig", timeSig));
            ar(make_nvp("bpm", bpm));
        }
    };
}
