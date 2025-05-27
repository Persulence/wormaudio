module;

#include <JuceHeader.h>

export module ElementInstanceManager;

import element;
import ElementInstance;
import AudioContext;

namespace player
{
    using namespace element;

    export class ElementInstanceManager : public ElementInstanceContext, public juce::AudioSource
    {
        std::vector<ElementInstancePtr> active;
        std::mutex activeMutex;

        AudioContext audioContext;

        juce::AudioSampleBuffer accumulator;
    public:

        ElementInstancePtr createInstance(const Element& element) override
        {
            // tODO: look into reusing identical instances
            std::lock_guard lock(activeMutex);
            return active.emplace_back(element.createInstance(audioContext));
        }

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
        {
            audioContext = {samplesPerBlockExpected, sampleRate};

            // TODO: channels
            accumulator = juce::AudioSampleBuffer(2, samplesPerBlockExpected);
        }

        void releaseResources() override
        {
            audioContext = {};
        }

        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
        {
            std::lock_guard lock(activeMutex); // Prevent the iterator from being invalidated
            for (auto& instance : active)
            {
                instance->getNextAudioBlock(bufferToFill);
            }

            // TODO tracks/buses
        }
    };
}

