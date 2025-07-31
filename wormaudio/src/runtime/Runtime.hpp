// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
