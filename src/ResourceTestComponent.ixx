module;

#include <juce_audio_utils/juce_audio_utils.h>

export module ResourceTestComponent;

import AudioContext;
import ResourceLoader;
import Resource;
import element;
import ElementTypes;
import ElementInstance;
import ElementInstanceManager;

import control;
import event;

export class ResourceTestComponent : public juce::AudioAppComponent
{
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ResourceTestComponent)

    player::AudioContext audioContext;
    resource::Resource::Ptr testResource;
    player::ElementInstanceManager manager;

    std::unique_ptr<event::StateManager> stateManager;

public:
    ResourceTestComponent()
    {
        using namespace resource;
        using namespace sm;
        using namespace element;

        ResourceLoader::Ptr loader = std::make_shared<ResourceLoader>();

        juce::File file = juce::File{"../fighter_attack.wav"};
        testResource = std::make_shared<Resource>(loader, file);

        // Create some states
        State::Ptr initialState = std::make_shared<State>();
        State::Ptr soundState = std::make_shared<State>();
        std::shared_ptr<Element> element = std::make_shared<ClipElement>(testResource);

        // Add an element to the second state
        soundState->insertElement(element);

        initialState->insertTransition(Transition1{ConditionList{std::vector<Condition>{TrueCondition{}}}, soundState});

        // Simulate instantiating the event
        stateManager = std::make_unique<event::StateManager>(std::vector{initialState, soundState});

        setAudioChannels(0, 2);
    }

    ~ResourceTestComponent() override
    {
        shutdownAudio();
    }

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        audioContext = {samplesPerBlockExpected, sampleRate};

        using namespace sm;
        using namespace player;
        using namespace event;

        manager.prepareToPlay(samplesPerBlockExpected, sampleRate);

        ParameterLookup lookup;

        // Do one logic tick
        stateManager->logicTick(lookup, manager);
    }

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
