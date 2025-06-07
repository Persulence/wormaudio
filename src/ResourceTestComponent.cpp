module;

#include <runtime/Runtime.hpp>
#include <memory>
#include <juce_audio_utils/juce_audio_utils.h>

module ui;

import :ResourceTestComponent;

import AudioContext;
import Resource;
import element;
import ElementTypes;
import ElementInstance;
import ElementInstanceManager;

import sm;
import event;

ResourceTestComponent::ResourceTestComponent()
{
    using namespace resource;
    using namespace sm;
    using namespace element;

    ResourceLoader::Ptr loader = runtime::getResourceLoader();

    // Create a sample element from a lazy resource
    juce::File file = juce::File{"../fighter_attack.wav"};
    testResource = std::make_shared<Resource>(loader, file);
    std::shared_ptr<Element> element = std::make_shared<ClipElement>(testResource);

    // Create some states
    StateDef::Ptr initialState = std::make_shared<StateDef>();
    StateDef::Ptr playState = std::make_shared<StateDef>();

    // Add a transition to the second state from the first state
    initialState->insertTransition(std::make_shared<Transition1>(condition::ConditionList{}, playState));
    // Add an element to the second state
    // playState->insertElement(element);

    event = event::Event::create();

    // Instantiate the event
    event->getDefinition()->insert(initialState, playState);
    instance = event->instantiate();

    setAudioChannels(0, 2);
}

void ResourceTestComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    audioContext = {samplesPerBlockExpected, sampleRate};

    using namespace sm;
    using namespace player;
    using namespace event;

    manager.prepareToPlay(samplesPerBlockExpected, sampleRate);

    ParameterLookup lookup;

    // Do one logic tick
    auto transport = TransportControl{};
    instance->logicTick(lookup, manager, transport);
}
