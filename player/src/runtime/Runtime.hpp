#pragma once

#include <memory>

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>

#include  "AudioEntryPoint.hpp"
#include "LogicTicker.hpp"
#include "../event/ParameterList.hpp"
#include "event/EventInstance.hpp"
#include "resource/Resource.fwd.hpp"
#include "resource/Asset.hpp"
#include "resource/ResourceLoader.hpp"

namespace runtime
{
    class Runtime;

    inline asset::ResourceLoader::Ptr getResourceLoader()
    {
        return asset::ResourceLoader::getInstance();
    }

    inline asset::AssetHandle createResource(const juce::File& file)
    {
        return std::make_shared<asset::Asset>(getResourceLoader(), file);
    }

    class Runtime : AudioEntryPoint, player::TransportCallback::Listener
    {
        std::vector<event::EventInstance::Ptr> instances;
        player::ElementInstanceManager elementManager;
        sm::ParameterLookup parameters;

        std::unique_ptr<LogicTicker> logicTicker;

    public:
        player::TransportControl transport;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Runtime)

        Runtime();

        void connectToDevice();
        void disconnect();

        // void setupParameters(std::shared_ptr<event::ParameterList> list);
        sm::ParameterLookup& getParameters();

        event::EventInstance::Ptr instantiate(const event::Event::Ptr &event);
        void addInstance(const event::EventInstance::Ptr &instance);
        void clearInstances();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void releaseResources() override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

        void logicTick();

    private:
    };

}
