// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <instance/ListenerInstance.hpp>
#include <juce_audio_basics/juce_audio_basics.h>

#include "instance/instance.hpp"
#include "resource/ElementInstance.hpp"
#include "util/AudioContext.hpp"
#include "util/Time.hpp"
#include "event/EventDef.fwd.hpp"

namespace player
{
    using namespace element;

    class ElementInstanceManager
    {
    public:
        ElementInstanceManager(const instance::Vec3f& position, const event::EventProperties& properties);

        ElementInstancePtr addInstance(const ElementInstancePtr& element);
        void stageHandoff(Sample sample);

        void clear();
        void freeReleased();

        void prepareToPlay(AudioContext context);
        void releaseResources();
        void getNextAudioBlock(const juce::AudioSourceChannelInfo &mainAccumulator, const instance::ListenerInstance &listenerInstance);

        [[nodiscard]] AudioContext getAudioContext() const { return audioContext; }

    private:
        // std::vector<ElementInstancePtr> active;
        // Using a collection type that does not allow duplicates
        // TODO: look into using data-oriented principles

        std::queue<ElementInstancePtr> queue;
        std::unordered_set<ElementInstancePtr> active;

        std::mutex activeMutex;

        AudioContext audioContext;

        juce::AudioSampleBuffer accumulator;

        Sample stagedHandoff{NULL_SAMPLE};
        const instance::Vec3f& position;
        const event::EventProperties& properties;
    };
}

