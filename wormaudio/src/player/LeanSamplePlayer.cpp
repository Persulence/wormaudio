// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "LeanSamplePlayer.hpp"

#include <cassert>

using namespace player;

LeanSamplePlayer::LeanSamplePlayer(asset::ElementSampleBuffer::Ptr buffer_, bool loop_):
    buffer(std::move(buffer_)), loop(loop_)
{
    formatManager.registerBasicFormats();
}

void LeanSamplePlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    auto numBufferChannels = buffer->getNumChannels();
    if (transportState == STOPPED || numBufferChannels == 0)
    {
        return;
    }

    auto numOutputChannels = bufferToFill.buffer->getNumChannels();
    auto outputSamplesRemaining = bufferToFill.numSamples;
    auto outputSamplesOffset = bufferToFill.startSample;

    // Buffer length and apparent length
    const int N = buffer->getNumSamples();
    const int N1 = static_cast<int>(static_cast<float>(N) / speed);

    while (outputSamplesRemaining > 0)
    {
        int sourceSamplesRemaining = N1 - position;

        int samplesThisTime = std::min(outputSamplesRemaining, sourceSamplesRemaining);

        float startGain = gain;
        float endGain = gain;

        if (transportState == STARTING)
        {
            startGain = 0;
            transportState = PLAYING;
        }

        if (transportState == STOPPING)
        {
            endGain = 0;
            transportState = STOPPED;
        }

        if (juce::approximatelyEqual(speed, 1.f))
        {

            for (auto channel = 0; channel < numOutputChannels; ++channel)
            {
                bufferToFill.buffer->addFromWithRamp(channel,
                                                     outputSamplesOffset,
                                                     buffer->getReadPointer(channel % numBufferChannels) + position,
                                                     samplesThisTime,
                                                     startGain, endGain);
            }
        }
        else
        {
            for (auto channel = 0; channel < numOutputChannels; ++channel)
            {
                float sampleGain = startGain;
                float gainIncrement = (endGain - startGain) / samplesThisTime;
                for (int i = 0; i < samplesThisTime; ++i)
                {
                    // Magical interpolation that actually works
                    // No antialiasing filter in sight

                    int n = position + i;
                    const float n2f = std::fmod(static_cast<float>(n) * speed, static_cast<float>(N));
                    const int n20 = static_cast<int>(std::floor(n2f));
                    const int n21 = (n20 + 1) % N;
                    delta = n2f - static_cast<float>(n20);

                    float sample = sampleGain * std::lerp(
                        buffer->getSample(channel % numBufferChannels, n20),
                        buffer->getSample(channel % numBufferChannels, n21),
                        delta);
                    assert(outputSamplesOffset + i < bufferToFill.buffer->getNumSamples());
                    bufferToFill.buffer->addSample(channel, outputSamplesOffset + i, sample);

                    sampleGain += gainIncrement;
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

    // I've put the old code with no pitch shift here for testing

    // auto& ref = *buffer;
    //
    // auto numOutputChannels = bufferToFill.buffer->getNumChannels();
    // auto outputSamplesRemaining = bufferToFill.numSamples;
    // auto outputSamplesOffset = bufferToFill.startSample;
    //
    // while (outputSamplesRemaining > 0)
    // {
    //     auto refSamplesRemaining = buffer->getNumSamples() - position;
    //     auto samplesThisTime = juce::jmin (outputSamplesRemaining, refSamplesRemaining);
    //     for (auto channel = 0; channel < numOutputChannels; ++channel)
    //     {
    //         bufferToFill.buffer->addFrom(channel,
    //                                      outputSamplesOffset,
    //                                      ref,
    //                                      channel % numBufferChannels,
    //                                      position,
    //                                      samplesThisTime,
    //                                      gain);
    //     }
    //     outputSamplesRemaining -= samplesThisTime;
    //     outputSamplesOffset += samplesThisTime;
    //     position += samplesThisTime;
    //
    //     if (position == ref.getNumSamples())
    //     {
    //         position = 0;
    //         if (!loop)
    //         {
    //             transportState = STOPPED;
    //             // Do nothing as this is additive
    //             // bufferToFill.buffer->clear(outputSamplesOffset, bufferToFill.numSamples - outputSamplesOffset);
    //             break;
    //         }
    //     }
    // }
}

void LeanSamplePlayer::changeState(TransportState state)
{
    switch (state)
    {
        case STARTING:
        {
            transportState = STARTING;
            break;
        }
        case STOPPING:
        {
            transportState = STOPPING;
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
