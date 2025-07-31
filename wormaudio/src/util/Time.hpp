// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once
#include <chrono>

#include "Data.hpp"

namespace player
{
    using Seconds = double;
    using Beats = double;
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

            return beats / ((*bpm / 60) * base);
        }

        util::Data<TimeSignature> getTimeSig() const
        {
            return timeSig;
        }

        double secondsToBeats(const double seconds) const
        {
            const double base = static_cast<double>(timeSig.getValue().denominator) / 4;

            return seconds * ((*bpm / 60) * base);
        }

        INTERNAL_SERIALIZE
        {
            using namespace cereal;
            ar(make_nvp("timeSig", timeSig));
            ar(make_nvp("bpm", bpm));
        }

    };
}
