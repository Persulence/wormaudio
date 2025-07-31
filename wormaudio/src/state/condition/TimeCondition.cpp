// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "TimeCondition.hpp"

#include "event/LogicTickInfo.hpp"
#include "state/EventParameterLookup.hpp"

namespace condition
{
    player::Sample TimeCondition::testImpl(const sm::EventParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance& currentState) const
    {
        auto reference = pl.getReference(time.type);

        const player::Sample timePoint = reference + info.toSamples(*time.valueSeconds);
        if (op == TimeOperator::GREATER_EQUAL)
        {
            if (timePoint >= info.blockBeginSamples && timePoint < info.blockEndSamples)
            {
                return timePoint - info.blockBeginSamples;
            }
            else if (info.blockBeginSamples >= timePoint)
            {
                // If time.value is less than the length of a block, and the previous transition occurs with a non-zero
                // handoff offset, it will not be possible to perform the next transition until the next block.
                return 0;
            }
        }
        else if (op == TimeOperator::LESS_EQUAL)
        {
            if (info.blockBeginSamples <= timePoint)
            {
                return 0;
            }
            else if (timePoint >= info.blockBeginSamples && timePoint < info.blockEndSamples)
            {
                return timePoint - info.blockBeginSamples;
            }
        }

        return -1;
    }
}
