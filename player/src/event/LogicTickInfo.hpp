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

        player::Sample toSamples(const player::Seconds value) const
        {
            return std::chrono::duration_cast<std::chrono::duration<int>>(value / (1. / sampleRate)).count();
        }
    };
}
