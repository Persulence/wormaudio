// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "ElementInstanceManager.hpp"

#include <numbers>

#include <instance/ListenerInstance.hpp>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_opengl/opengl/juce_gl.h>

#include "instance/spatial.hpp"
#include "resource/ElementInstance.hpp"
#include "event/EventProperties.hpp"

namespace player
{
    ElementInstanceManager::ElementInstanceManager(const instance::Vec3f& position, const event::EventProperties& properties):
        position(position), properties(properties)
    {

    }

    ElementInstancePtr ElementInstanceManager::addInstance(const ElementInstancePtr& element)
    {
        // tODO: look into reusing identical instances
        std::lock_guard lock(activeMutex);
        return queue.emplace(element);
    }

    void ElementInstanceManager::stageHandoff(const Sample sample)
    {
        stagedHandoff = sample;
    }

    void ElementInstanceManager::clear()
    {
        std::lock_guard lock(activeMutex);
        active.clear();
    }

    void ElementInstanceManager::freeReleased()
    {
        std::lock_guard lock(activeMutex);
        std::erase_if(active, [](const auto& e)
        {
            return e->canBeFreed();
        });

        // if (active.size() != prev)
        // {
            // std::cout << "an erasing day " << prev - active.size() << "\n";
        // }
    }

    void ElementInstanceManager::prepareToPlay(AudioContext context)
    {
        audioContext = context;

        // TODO: channels
        accumulator = juce::AudioSampleBuffer(2, context.samplesPerBlock);
    }

    void ElementInstanceManager::releaseResources()
    {
        audioContext = {};
    }

    void ElementInstanceManager::getNextAudioBlock(const juce::AudioSourceChannelInfo &mainAccumulator, instance::ListenerInstance listenerInstance)
    {
        // Use a different buffer, as the main one is not meant to be cleared.
        const juce::AudioSourceChannelInfo accumulatorInfo{&accumulator, mainAccumulator.startSample, mainAccumulator.numSamples};

        if (stagedHandoff != NULL_SAMPLE)
        {
            // TODO: stop locking the audio thread!!!!!
            std::lock_guard lock(activeMutex);

            // Generate the block using current elements
            for (auto& instance : active)
            {
                instance->getNextAudioBlock(accumulatorInfo);
            }

            // Clear the end of the buffer
            auto startSample = accumulatorInfo.startSample + stagedHandoff;
            auto numSamples = accumulatorInfo.numSamples - startSample;
            accumulatorInfo.buffer->clear(startSample, numSamples);

            // Remove finished elements
            std::erase_if(active, [](const auto& e) { return e->canBeFreed(); });

            // Add queued elements
            while (!queue.empty())
            {
                active.insert(queue.front());
                queue.pop();
            }

            // Fill the remaining portion of the buffer
            juce::AudioSourceChannelInfo info2{accumulatorInfo.buffer, startSample, numSamples};
            for (auto& instance : active)
            {
                instance->getNextAudioBlock(info2);
            }

            stagedHandoff = NULL_SAMPLE;
        }
        else
        {
            accumulator.clear();

            // TODO: Ensure that this thread can always acquire the lock
            std::lock_guard lock(activeMutex); // Prevent the iterator from being invalidated
            for (auto& instance : active)
            {
                instance->getNextAudioBlock(accumulatorInfo);
            }
        }

        auto soundPos = position;
        auto listenerPos = listenerInstance.position;

        float result = earDistance(soundPos, listenerPos, listenerInstance.yaw, properties.maxDistance);
        float distance = (soundPos - listenerPos).abs();

        float attenuation = properties.attenuate(distance);

        float theta = (result + 1.f) * std::numbers::pi / 4;

        // Constant power
        constexpr float c = 1.4142; // Makes centre pan equivalent to listening to both channels with unity gain.
        float leftGain = std::cos(theta) * c * attenuation;
        float rightGain = std::sin(theta) * c * attenuation;

        // Linear
        // ???

        mainAccumulator.buffer->addFrom(0, mainAccumulator.startSample, *accumulatorInfo.buffer,
            0, accumulatorInfo.startSample, accumulatorInfo.numSamples,
            leftGain);
        mainAccumulator.buffer->addFrom(1, mainAccumulator.startSample, *accumulatorInfo.buffer,
            1, accumulatorInfo.startSample, accumulatorInfo.numSamples,
            rightGain);

        // TODO: buses
    }
}
