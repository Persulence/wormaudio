// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
        TransportCallback1 transportCallback{[](TransportState){}};

        AudioContext audioContext;

        int position{0};

        float gain = 1;

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

        void setTransportCallback(TransportCallback1 callback) override
        {
            transportCallback = callback;
        }

        void changeState(TransportState state) override
        {
            switch (state)
            {
                case STARTING:
                {
                    transportState = PLAYING;
                    transportCallback(transportState);
                    break;
                }
                case STOPPING:
                {
                    transportState = STOPPED;
                    transportCallback(transportState);
                    break;
                }
                case PLAYING:
                {
                    transportState = PLAYING;
                    break;
                }
                case STOPPED:
                {
                    transportState = STOPPED;
                    break;
                }
            }
        }
    };

}
