// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include "util/AudioContext.hpp"
#include "util/Time.hpp"

namespace event
{
    struct LogicTickInfo
    {
        explicit LogicTickInfo(const player::AudioContext &context, player::Sample blockBeginSamples_):
            sampleRate(context.sampleRate),
            samplesPerBlock(context.samplesPerBlock),
            blockDuration(context.samplesPerBlock / context.sampleRate),
            blockBeginSamples(blockBeginSamples_),
            blockEndSamples(blockBeginSamples + samplesPerBlock),
            blockBegin(blockBeginSamples_ * context.sampleDuration),
            blockEnd(blockBegin + blockDuration)
        {

        }

        double sampleRate;
        player::Sample samplesPerBlock;
        player::Sample blockBeginSamples;
        player::Sample blockEndSamples;
        player::Seconds blockDuration;
        player::Seconds blockBegin;
        player::Seconds blockEnd;

        [[nodiscard]] player::Sample toSamples(const player::Seconds value) const
        {
            // return std::chrono::duration_cast<std::chrono::duration<int>>(value / (1. / sampleRate)).count();
            return static_cast<player::Sample>(value / (1. / sampleRate));
        }
    };
}
