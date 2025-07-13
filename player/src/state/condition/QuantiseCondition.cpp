// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "QuantiseCondition.hpp"

#include "state/EventParameterLookup.hpp"

namespace condition
{
    QuantiseCondition::QuantiseCondition()
    {
    }

    player::Sample QuantiseCondition::testImpl(const sm::EventParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance& currentState) const
    {
        const auto reference = pl.getReference(player::IN_STATE);

        player::Seconds interval1 = *intervalSeconds;
        if (interval1 > 0)
        {
            auto intervalSamples = info.toSamples(interval1);

            auto bbReference = info.blockBeginSamples - reference;

            // Divide adjusted block begin by interval, floor, add 1, multiply by interval to get next quantise point.
            const auto nextPoint = reference + (std::floor(bbReference / static_cast<double>(intervalSamples)) + 1) * intervalSamples;

            if (nextPoint >= info.blockBeginSamples && nextPoint < info.blockEndSamples)
            {
                return nextPoint - info.blockBeginSamples;
            }
        }

        return -1;
    }
}
