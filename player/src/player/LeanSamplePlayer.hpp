#pragma once

#include <JuceHeader.h>

#include <utility>

#include "SamplePlayer1.hpp"
#include "resource/ElementSampleBuffer.hpp"
#include "util/AudioContext.hpp"

import transport;
import io;

namespace player
{
    class LeanSamplePlayer : public SamplePlayer
    {
        resource::ElementSampleBuffer::Ptr buffer;
        juce::AudioFormatManager formatManager;
        TransportState transportState{STOPPED};
        TransportCallback1 transportCallback{[](TransportState){}};

        AudioContext audioContext;

        int position{0};

        float gain = 1;

    public:
        bool loop;

        explicit LeanSamplePlayer(resource::ElementSampleBuffer::Ptr buffer_, bool loop_);

        explicit LeanSamplePlayer(): LeanSamplePlayer(resource::EMPTY_BUFFER, false)
        {
        }

        void setBuffer(resource::ElementSampleBuffer::Ptr buffer_)
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
