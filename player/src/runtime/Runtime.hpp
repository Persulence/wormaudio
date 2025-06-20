#pragma once

#include "Runtime.fwd.hpp"

#include <memory>

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>

#include  "AudioEntryPoint.hpp"
#include "event/EventInstance.hpp"

namespace runtime
{
    class Runtime;

    class Runtime : AudioEntryPoint, player::TransportCallback::Listener
    {
        std::vector<event::EventInstance::Ptr> instances;
        player::ElementInstanceManager elementManager;
        sm::ParameterLookup parameters;

    public:
        player::TransportControl transport;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Runtime)

        Runtime();

        void connectToDevice();
        void disconnect();

        // void setupParameters(std::shared_ptr<event::ParameterList> list);
        sm::ParameterLookup& getParameters();

        event::EventInstance::Ptr instantiate(const resource::Handle<event::EventDef> &event);
        void addInstance(const event::EventInstance::Ptr &instance);
        void clearInstances();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void releaseResources() override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

        void logicTick();

    private:
    };

}
