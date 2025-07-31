// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include "juce_audio_basics/juce_audio_basics.h"

#include <utility>

#include "SamplePlayer1.hpp"
#include "resource/ElementSampleBuffer.hpp"
#include "util/AudioContext.hpp"
#include "util/io.hpp"

namespace player
{
    class LeanSamplePlayer : public SamplePlayer
    {
        asset::ElementSampleBuffer::Ptr buffer;
        juce::AudioFormatManager formatManager;
        TransportState transportState{STOPPED};

        AudioContext audioContext;

        int position{0};
        float delta{0};

        float gain = 1;

        float speed{1};
        float n1;

    public:
        bool loop;

        explicit LeanSamplePlayer(asset::ElementSampleBuffer::Ptr buffer_, bool loop_);

        explicit LeanSamplePlayer(): LeanSamplePlayer(std::make_shared<asset::ElementSampleBuffer>(), false)
        {
        }

        void setBuffer(asset::ElementSampleBuffer::Ptr buffer_)
        {
            // TODO: synchronisation
            buffer = std::move(buffer_);
        }

        void setGainDb(const float volumeDb_)
        {
            gain = juce::Decibels::decibelsToGain(volumeDb_);
        }

        void setFile(juce::File &&file) override
        {
            io::readFile(file, formatManager, *buffer, 40);
        }

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
        {
            audioContext = {samplesPerBlockExpected, sampleRate};
        }

        void releaseResources() override
        {

        }

        TransportState getState() const
        {
            return transportState;
        }

        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

        void changeState(TransportState state) override;

        void setPitch(const float pitchFactor)
        {
            // Why did I think that speed and pitch were inversely proportional?
            // What is wrong with me?

            setSpeed(pitchFactor);
        }

        void setSpeed(const float speed_);
    };

}
