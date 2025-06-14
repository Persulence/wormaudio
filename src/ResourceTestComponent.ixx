module;

#include <juce_audio_utils/juce_audio_utils.h>

#include "resource/ClipElement.hpp"

export module ui:ResourceTestComponent;

import AudioContext;
import resource;
import element;
import ElementInstance;
import ElementInstanceManager;

import sm;
import event;

export class ResourceTestComponent : public juce::AudioAppComponent
{
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ResourceTestComponent)

    player::AudioContext audioContext;
    resource::Resource::Ptr testResource;
    player::ElementInstanceManager manager;

    event::Event::Ptr event;
    event::EventInstance::Ptr instance;

public:
    ResourceTestComponent();

    ~ResourceTestComponent() override
    {
        shutdownAudio();
    }

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    void releaseResources() override
    {
    }

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
    {
        manager.getNextAudioBlock(bufferToFill);
    }

    void paint(juce::Graphics &g) override
    {

    }

    void resized() override
    {

    }
};
