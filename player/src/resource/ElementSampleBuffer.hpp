#pragma once

#include <memory>
#include "juce_audio_basics/juce_audio_basics.h"

namespace resource
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
