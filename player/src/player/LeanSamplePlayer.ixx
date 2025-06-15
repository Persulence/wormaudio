module;

#include <JuceHeader.h>

#include <utility>

#include "util/AudioContext.hpp"

export module LeanSamplePlayer;

import SamplePlayer;
import transport;
import ElementSampleBuffer;
import io;

namespace player
{
    export class LeanSamplePlayer : public SamplePlayer
    {
        resource::ElementSampleBuffer::Ptr buffer;
        juce::AudioFormatManager formatManager;
        TransportState transportState{STOPPED};
        TransportCallback1 transportCallback{[](TransportState){}};

        AudioContext audioContext;

        int position{0};

        // bool additive{true};

        float gain = 1;

    public:
        explicit LeanSamplePlayer(resource::ElementSampleBuffer::Ptr buffer_):
            buffer(std::move(buffer_))
        {
            formatManager.registerBasicFormats();
        }

        explicit LeanSamplePlayer(): LeanSamplePlayer(resource::EMPTY_BUFFER)
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

        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
        {
            const auto& ref = *buffer;

            auto numBufferChannels = ref.getNumChannels();
            if (transportState != PLAYING || numBufferChannels == 0)
            {
                bufferToFill.clearActiveBufferRegion();
                return;
            }

            auto numOutputChannels = bufferToFill.buffer->getNumChannels();
            auto outputSamplesRemaining = bufferToFill.numSamples;
            auto outputSamplesOffset = bufferToFill.startSample;

            while (outputSamplesRemaining > 0)
            {
                auto refSamplesRemaining = buffer->getNumSamples() - position;
                auto samplesThisTime = juce::jmin (outputSamplesRemaining, refSamplesRemaining);
                for (auto channel = 0; channel < numOutputChannels; ++channel)
                {
                    bufferToFill.buffer->addFrom(channel,
                        outputSamplesOffset,
                        ref,
                        channel % numBufferChannels,
                        position,
                        samplesThisTime,
                        gain);
                }
                outputSamplesRemaining -= samplesThisTime;
                outputSamplesOffset += samplesThisTime;
                position += samplesThisTime;

                if (position == ref.getNumSamples())
                {
                    position = 0;
                    transportState = STOPPED;
                    bufferToFill.buffer->clear(outputSamplesOffset, bufferToFill.numSamples - outputSamplesOffset);
                    break;
                }
            }
        }

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
