module;

#include <JuceHeader.h>

export module LeanSamplePlayer;

import SamplePlayer;
import transport;
import ElementSampleBuffer;
import io;
import AudioContext;

namespace player
{
    export class LeanSamplePlayer : public SamplePlayer
    {
        resource::ElementSampleBuffer::Ptr buffer;
        juce::AudioFormatManager formatManager;
        TransportState transportState{STOPPED};
        TransportCallback transportCallback{[](TransportState){}};

        AudioContext audioContext;

        int position{0};

    public:

        explicit LeanSamplePlayer(resource::ElementSampleBuffer::Ptr buffer_):
            buffer(std::move(buffer_))
        {
            formatManager.registerBasicFormats();
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
                    bufferToFill.buffer->copyFrom(channel,
                        outputSamplesOffset,
                        ref,
                        channel % numBufferChannels,
                        position,
                        samplesThisTime);
                }
                outputSamplesRemaining -= samplesThisTime;
                outputSamplesOffset += samplesThisTime;
                position += samplesThisTime;

                if (position == ref.getNumSamples())
                    position = 0;
            }
        }

        void setTransportCallback(TransportCallback callback) override
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
