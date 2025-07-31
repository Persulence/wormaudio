// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
