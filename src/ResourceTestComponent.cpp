module;

#include <memory>
#include <juce_audio_utils/juce_audio_utils.h>

module ui;

import :ResourceTestComponent;

import AudioContext;
import ResourceLoader;
import Resource;
import element;
import ElementTypes;
import ElementInstance;
import ElementInstanceManager;

import control;
import event;

ResourceTestComponent::ResourceTestComponent() {
    using namespace resource;
    using namespace sm;
    using namespace element;

    ResourceLoader::Ptr loader = std::make_shared<ResourceLoader>();

    // Create a sample element from a lazy resource
    juce::File file = juce::File{"../fighter_attack.wav"};
    testResource = std::make_shared<Resource>(loader, file);
    std::shared_ptr<Element> element = std::make_shared<ClipElement>(testResource);

    // Create some states
    State::Ptr initialState = std::make_shared<State>();
    State::Ptr playState = std::make_shared<State>();

    // Add a transition to the second state from the first state
    initialState->insertTransition(Transition1{ConditionList{std::vector<Condition>{TrueCondition{}}}, playState});
    // Add an element to the second state
    playState->insertElement(element);

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
    instance->logicTick(lookup, manager);
}
