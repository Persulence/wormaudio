#include "LeanSamplePlayer.hpp"

using namespace player;

LeanSamplePlayer::LeanSamplePlayer(resource::ElementSampleBuffer::Ptr buffer_, bool loop_):
    buffer(std::move(buffer_)), loop(loop_)
{
    formatManager.registerBasicFormats();
}

void LeanSamplePlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    const auto& ref = *buffer;

    auto numBufferChannels = ref.getNumChannels();
    if (transportState != PLAYING || numBufferChannels == 0)
    {
        // Do nothing as this is additive
        // bufferToFill.clearActiveBufferRegion();
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
            if (!loop)
            {
                transportState = STOPPED;
                // Do nothing as this is additive
                // bufferToFill.buffer->clear(outputSamplesOffset, bufferToFill.numSamples - outputSamplesOffset);
                break;
            }
        }
    }
}
