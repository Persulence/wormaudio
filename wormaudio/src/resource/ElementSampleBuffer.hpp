// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <memory>
#include "juce_audio_basics/juce_audio_basics.h"

namespace asset
{
    class ElementSampleBuffer : public juce::AudioBuffer<float>
    {
    public:
        using Ptr = std::shared_ptr<ElementSampleBuffer>;

        static Ptr create();

        ElementSampleBuffer() = default;
    };

    const extern std::shared_ptr<ElementSampleBuffer> EMPTY_BUFFER;
}
