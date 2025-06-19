module;

#include <vector>

#include <juce_audio_basics/juce_audio_basics.h>

#include "resource/ElementInstance.hpp"
#include "util/AudioContext.hpp"

export module ElementInstanceManager;

namespace player
{
    using namespace element;

    export class ElementInstanceManager : public juce::AudioSource
    {
        std::vector<ElementInstancePtr> active;
        std::mutex activeMutex;

        AudioContext audioContext;

        juce::AudioSampleBuffer accumulator;
    public:
        ElementInstancePtr addInstance(const ElementInstancePtr& element);

        void clear();
        void freeReleased();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void releaseResources() override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

        [[nodiscard]] AudioContext getAudioContext() const { return audioContext; }
    };
}

