module;

#include <juce_audio_utils/juce_audio_utils.h>

export module ResourceTestComponent;

import AudioContext;
import ResourceLoader;
import Resource;
import element;
import ElementTypes;
import ElementInstance;

export class ResourceTestComponent : public juce::AudioAppComponent
{
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ResourceTestComponent)

    player::AudioContext audioContext;
    resource::Resource::Ptr testResource;
    element::ElementInstancePtr elementInstance;

public:
    ResourceTestComponent()
    {
        using namespace resource;

        ResourceLoader::Ptr loader = std::make_shared<ResourceLoader>();

        juce::File file = juce::File{"../fighter_attack.wav"};
        testResource = std::make_shared<Resource>(loader, file);

        setAudioChannels(0, 2);
    }

    ~ResourceTestComponent() override
    {
        shutdownAudio();
    }

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        audioContext = {samplesPerBlockExpected, sampleRate};

        using namespace element;
        std::shared_ptr<Element> element = std::make_shared<ClipElement>(testResource);
        elementInstance = element->createInstance(audioContext);
        elementInstance->start();
    }

    void releaseResources() override
    {
    }

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
    {
        if (elementInstance != nullptr)
        {
            elementInstance->getNextAudioBlock(bufferToFill);
        }
    }

    void paint(juce::Graphics &g) override
    {

    }

    void resized() override
    {

    }
};
