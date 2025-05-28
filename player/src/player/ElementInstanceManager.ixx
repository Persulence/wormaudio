module;

#include <vector>

#include <juce_audio_basics/juce_audio_basics.h>

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

        ElementInstancePtr createInstance(const Element& element) override;

        void clear();
        void freeReleased();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void releaseResources() override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
    };
}

