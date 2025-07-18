// Copyright (c) 2025 Thomas Paley-Menzies
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
    const auto& ref = *buffer;

    auto numBufferChannels = ref.getNumChannels();
    // if (transportState != PLAYING || numBufferChannels == 0)
    // {
        // return;
    // }

    auto numOutputChannels = bufferToFill.buffer->getNumChannels();
    auto outputSamplesRemaining = bufferToFill.numSamples;
    auto outputSamplesOffset = bufferToFill.startSample;

    float pitch = 1;

    int samplesThisTime = bufferToFill.numSamples;

    int N = buffer->getNumSamples();

    for (auto channel = 0; channel < numOutputChannels; ++channel)
    {
        for (int i = 0; i < samplesThisTime; ++i)
        {
            int n = position + i;
            float n2f = std::fmod(static_cast<float>(n) / pitch, N);
            int n20 = static_cast<int>(std::floor(n2f));
            int n21 = (n20 + 1) % N;
            delta = n2f - n20;

            if (n >= buffer->getNumSamples())
            {
                int ooo = 1;
            }

            // REMOVE
            int _n20 = n % N;
            int _n21 = (n + 1) % N;
            // delta = 0;

            // float sample = ref.getSample(channel % numBufferChannels, n20) * gain;
            float sample = std::lerp(
                buffer->getSample(channel % numBufferChannels, n20),
                buffer->getSample(channel % numBufferChannels, n21),
                delta);
            bufferToFill.buffer->addSample(channel, outputSamplesOffset + i, sample);
        }
    }

    position += samplesThisTime;
    if (position >= buffer->getNumSamples())
    {
        // transportState = STOPPED;
        // position = 0;
        position = (position + samplesThisTime) % N;
    }

    // position += std::floor(static_cast<float>(samplesThisTime) * pitch);

    // while (outputSamplesRemaining > 0)
    // {
    //     auto refSamplesRemaining = buffer->getNumSamples() - position;
    //     auto samplesThisTime = juce::jmin(outputSamplesRemaining, refSamplesRemaining);
    //     for (auto channel = 0; channel < numOutputChannels; ++channel)
    //     {
    //         // bufferToFill.buffer->addFrom(channel,
    //         //                              outputSamplesOffset,
    //         //                              ref,
    //         //                              channel % numBufferChannels,
    //         //                              position,
    //         //                              samplesThisTime,
    //         //                              gain);
    //
    //         for (int i = 0; i < samplesThisTime; ++i)
    //         {
    //             bufferToFill.buffer->addSample(channel, outputSamplesOffset + i,
    //                 ref.getSample(channel % numBufferChannels, position + i) * gain);
    //         }
    //     }
    //
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
    //             break;
    //         }
    //     }
    // }
}
