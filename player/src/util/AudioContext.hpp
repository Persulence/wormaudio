// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
