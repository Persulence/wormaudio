module;

#include <JuceHeader.h>

export module Track;

import ElementInstance;
import ElementInstanceContext;

export class Track : public juce::AudioSource
{
        std::vector<element::ElementInstancePtr> active;

public:
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {

    }

    void releaseResources() override
    {
        active.clear();
    }

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
    {
        for (const auto& instance : active)
        {
            instance->getNextAudioBlock(bufferToFill);
        }
    }
};