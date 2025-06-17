#pragma once

#include <memory>
#include <juce_audio_utils/juce_audio_utils.h>

namespace resource
{
    class ElementSampleBuffer : public juce::AudioBuffer<float>
    {
    public:
        using Ptr = std::shared_ptr<ElementSampleBuffer>;

        static Ptr create();

        ElementSampleBuffer() = default;
    };

    const auto EMPTY_BUFFER = std::make_shared<ElementSampleBuffer>();
}
