// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <memory>

#include <juce_audio_basics/juce_audio_basics.h>

#include "util/AudioContext.hpp"

namespace element
{
    class Element;

    class ElementInstance
    {
    protected:
        player::AudioContext audioContext;
        bool released;

    public:
        explicit ElementInstance(const player::AudioContext &context_):
            audioContext(context_),
            released(false)
        {
        }

        virtual Element* getParent() = 0;

        virtual void start() = 0;

        virtual void stop() = 0;

        virtual bool isDone() const = 0;

        virtual bool canBeFreed() const
        {
            return released;
        }


        virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToAdd) = 0;

        virtual ~ElementInstance() = default;
    };

    using ElementInstancePtr = std::shared_ptr<ElementInstance>;
}

