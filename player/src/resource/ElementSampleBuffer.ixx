module;

#include <memory>
#include <juce_audio_utils/juce_audio_utils.h>

export module ElementSampleBuffer;

namespace resource
{
    export class ElementSampleBuffer : public juce::AudioBuffer<float>
    {
    public:
        using Ptr = std::shared_ptr<ElementSampleBuffer>;

        static Ptr create();

        void thing();
    };

    export const ElementSampleBuffer::Ptr EMPTY_BUFFER = std::make_shared<ElementSampleBuffer>();
}
