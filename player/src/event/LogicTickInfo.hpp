// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
