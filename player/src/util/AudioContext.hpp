#pragma once

namespace player
{
    struct AudioContext
    {
        int samplesPerBlock;
        double sampleRate;
        double sampleDuration;
        bool initialised{false};

        AudioContext():
            samplesPerBlock(0),
            sampleRate(0),
            sampleDuration(1),
            initialised(false)
        {}

        AudioContext(int samplesPerBlock_, double sampleRate_):
            samplesPerBlock(samplesPerBlock_),
            sampleRate(sampleRate_),
            sampleDuration(1 / sampleRate),
            initialised(true)
        {}
    };
}
