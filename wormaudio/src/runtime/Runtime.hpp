// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "Runtime.fwd.hpp"

#include <memory>

#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_core/juce_core.h"

#include "AudioEntryPoint.hpp"
#include "event/EventInstance.hpp"
#include "instance/ListenerInstance.hpp"

namespace runtime
{
    class Runtime;

    class Runtime : AudioEntryPoint, player::TransportCallback::Listener
    {

    public:
        player::TransportControl transport;
        player::AudioContext audioContext;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Runtime)

        Runtime();

        ~Runtime() override;

        void connectToDevice();

        void disconnect();

        // void setupParameters(std::shared_ptr<event::ParameterList> list);

        sm::GlobalParameterLookup &getParameters();

        event::EventInstance::Ptr instantiate(const resource::Handle<event::EventDef> &event);

        void addInstance(const event::EventInstance::Ptr &instance);

        const std::vector<event::EventInstance::Ptr> &getInstances();
        void clearInstances();
        void pruneInstances();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void releaseResources() override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

        void setListenerPosition(const instance::Vec3f position) { listener.position = position; }
        void setListenerYaw(const float yaw) { listener.yaw = yaw; }

    private:
        struct SimpleTimer : juce::Timer
        {
            void timerCallback() override { callback(); }

            std::function<void()> callback;
        };

        std::vector<event::EventInstance::Ptr> instances;
        std::mutex instancesMutex;

        sm::GlobalParameterLookup parameters;

        SimpleTimer collectFreeInstances;

        player::Sample samplesPast{};

        instance::ListenerInstance listener;

        void logicTick();
    };

}
