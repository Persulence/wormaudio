#pragma once

#include <JuceHeader.h>

#include "resource/ElementInstance.hpp"

class Track : public juce::AudioSource
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
