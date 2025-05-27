#pragma once

#include <memory>

#include <juce_audio_basics/juce_audio_basics.h>
// #include <juce_audio_devices/juce_audio_devices.h>
#include <juce_core/juce_core.h>

#include  "AudioEntryPoint.hpp"
#include "LogicTicker.hpp"

import Resource;
import event;
import ElementInstanceManager;
import control;

namespace runtime
{
    class Runtime;

    inline resource::ResourceLoader::Ptr getResourceLoader()
    {
        return resource::ResourceLoader::getInstance();
    }

    inline resource::Resource::Ptr createResource(const juce::File& file)
    {
        return std::make_shared<resource::Resource>(getResourceLoader(), file);
    }

    class Runtime : AudioEntryPoint
    {
        std::vector<event::EventInstance::Ptr> instances;
        player::ElementInstanceManager elementManager;
        sm::ParameterLookup parameters;

        std::unique_ptr<LogicTicker> logicTicker;

    public:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Runtime);

        Runtime();

        void connectToDevice();
        void disconnect();

        event::EventInstance::Ptr instantiate(const event::Event::Ptr &event);
        void clearInstances();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void releaseResources() override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

        void logicTick();

    };

}
