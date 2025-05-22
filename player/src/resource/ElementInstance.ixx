module;

#include <memory>

#include <juce_audio_basics/juce_audio_basics.h>

export module ElementInstance;

import AudioContext;
import SamplePlayer;

namespace element
{
    export class ElementInstance
    {
    protected:
        player::AudioContext audioContext;
        bool released;

    public:
        explicit ElementInstance(const player::AudioContext &context_):
            audioContext(context_),
            released(false)
        {
        }

        virtual void start() = 0;

        virtual void stop() = 0;

        [[nodiscard]] bool canBeFreed() const
        {
            return released;
        }

        virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToAdd) = 0;

        virtual ~ElementInstance() = default;
    };

    export using ElementInstancePtr = std::shared_ptr<ElementInstance>;
}

