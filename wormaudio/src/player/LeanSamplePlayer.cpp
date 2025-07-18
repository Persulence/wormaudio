// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "LeanSamplePlayer.hpp"

using namespace player;

LeanSamplePlayer::LeanSamplePlayer(asset::ElementSampleBuffer::Ptr buffer_, bool loop_):
    buffer(std::move(buffer_)), loop(loop_)
{
    formatManager.registerBasicFormats();
}

void LeanSamplePlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    auto numBufferChannels = buffer->getNumChannels();
    if (transportState != PLAYING || numBufferChannels == 0)
    {
        return;
    }

    auto numOutputChannels = bufferToFill.buffer->getNumChannels();
    auto outputSamplesRemaining = bufferToFill.numSamples;
    auto outputSamplesOffset = bufferToFill.startSample;

    float speed = 1;

    // Buffer length and apparent length
    const int N = buffer->getNumSamples();
    const int N1 = N / speed;

    while (outputSamplesRemaining > 0)
    {
        int sourceSamplesRemaining = N1 - position;

        int samplesThisTime = std::min(outputSamplesRemaining, sourceSamplesRemaining);

        if (juce::approximatelyEqual(speed, 1.f))
        {
            for (auto channel = 0; channel < numOutputChannels; ++channel)
            {
                bufferToFill.buffer->addFrom(channel,
                                             outputSamplesOffset,
                                             *buffer,
                                             channel % numBufferChannels,
                                             position,
                                             samplesThisTime,
                                             gain);
            }
        }
        else
        {
            for (auto channel = 0; channel < numOutputChannels; ++channel)
            {
                for (int i = 0; i < samplesThisTime; ++i)
                {
                    int n = position + i;
                    float n2f = std::fmod(static_cast<float>(n) * speed, N);
                    int n20 = static_cast<int>(std::floor(n2f));
                    int n21 = (n20 + 1) % N;
                    delta = n2f - n20;

                    float sample = std::lerp(
                        buffer->getSample(channel % numBufferChannels, n20),
                        buffer->getSample(channel % numBufferChannels, n21),
                        delta);
                    bufferToFill.buffer->addSample(channel, outputSamplesOffset + i, sample);
                }
            }
        }

        outputSamplesRemaining -= samplesThisTime;
        outputSamplesOffset += samplesThisTime;
        position = position + samplesThisTime;

        if (position == N1)
        {
            position = 0;
            if (!loop)
            {
                transportState = STOPPED;
                break;
            }
        }
    }
}
