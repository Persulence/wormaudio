module;

#include <JuceHeader.h>

export module LeanSamplePlayer;

import SamplePlayer;
import transport;

namespace player
{
    export void readFile(const juce::File& file, juce::AudioFormatManager& formatManager, juce::AudioSampleBuffer& outputBuffer, float maxDuration)
    {
        if (file == juce::File{})
            return;

        const std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

        if (reader.get() != nullptr)
        {
            double duration = (reader->lengthInSamples / reader->sampleRate);
            if (duration < maxDuration)
            {
                outputBuffer.setSize(reader->numChannels, reader->lengthInSamples);
                reader->read(
                    &outputBuffer,
                    0,
                    reader->lengthInSamples,
                    0,
                    true,
                    true);

                // setAudioChannels(0, reader->numChannels);
            }
            else
            {
                // handle the error that the file is 2 seconds or longer..
                juce::String message = "file ";
                message << file.getFullPathName() << " longer than " << maxDuration << "s";
                juce::Logger::getCurrentLogger()->writeToLog(message);
            }
        }
    }

    export class LeanSamplePlayer : public SamplePlayer
    {
        juce::AudioSampleBuffer buffer;
        juce::AudioFormatManager formatManager;
        TransportState transportState{STOPPED};
        TransportCallback tranportCallback{[](TransportState){}};

        int position{0};

    public:

        LeanSamplePlayer()
        {
            formatManager.registerBasicFormats();
        }

        void setFile(::juce::File &&file) override
        {
            readFile(file, formatManager, buffer, 40);
        }

    private:

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
        {

        }

        void releaseResources() override
        {

        }

        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
        {
            auto numBufferChannels = buffer.getNumChannels();
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
                auto bufferSamplesRemaining = buffer.getNumSamples() - position;
                auto samplesThisTime = juce::jmin (outputSamplesRemaining, bufferSamplesRemaining);
                for (auto channel = 0; channel < numOutputChannels; ++channel)
                {
                    bufferToFill.buffer->copyFrom(channel,
                        outputSamplesOffset,
                        buffer,
                        channel % numBufferChannels,
                        position,
                        samplesThisTime);
                }
                outputSamplesRemaining -= samplesThisTime;
                outputSamplesOffset += samplesThisTime;
                position += samplesThisTime;

                if (position == buffer.getNumSamples())
                    position = 0;
            }
        }

        void setTransportCallback(TransportCallback callback) override
        {
            tranportCallback = callback;
        }

        void changeState(TransportState state) override
        {
            switch (state)
            {
                case STARTING:
                {
                    transportState = PLAYING;
                    tranportCallback(transportState);
                    break;
                }
                case STOPPING:
                {
                    transportState = STOPPED;
                    tranportCallback(transportState);
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
