// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "ElementInstanceManager.hpp"

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
        // std::lock_guard lock(activeMutex);
        return queue.emplace(element);
    }

    void ElementInstanceManager::stageHandoff(const Sample sample)
    {
        stagedHandoff = sample;
    }

    void ElementInstanceManager::clear()
    {
        // std::lock_guard lock(activeMutex);
        active.clear();
    }

    void ElementInstanceManager::freeReleased()
    {
        // std::lock_guard lock(activeMutex);
        // int prev = active.size();
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

    void ElementInstanceManager::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill, instance::ListenerInstance listenerInstance)
    {
        if (stagedHandoff != NULL_SAMPLE)
        {
            // std::lock_guard lock(activeMutex);

            // Generate the block using current elements
            for (auto& instance : active)
            {
                instance->getNextAudioBlock(bufferToFill);
            }

            // Clear the end of the buffer
            auto startSample = bufferToFill.startSample + stagedHandoff;
            auto numSamples = bufferToFill.numSamples - startSample;
            bufferToFill.buffer->clear(startSample, numSamples);

            // Remove finished elements
            std::erase_if(active, [](const auto& e) { return e->canBeFreed(); });

            // Add queued elements
            while (!queue.empty())
            {
                active.insert(queue.front());
                queue.pop();
            }

            // Fill the remaining portion of the buffer
            juce::AudioSourceChannelInfo info2{bufferToFill.buffer, startSample, numSamples};
            for (auto& instance : active)
            {
                instance->getNextAudioBlock(info2);
            }

            stagedHandoff = NULL_SAMPLE;
        }
        else
        {
            // TODO: Ensure that this thread can always acquire the lock
            // std::lock_guard lock(activeMutex); // Prevent the iterator from being invalidated
            for (auto& instance : active)
            {
                instance->getNextAudioBlock(bufferToFill);
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

        bufferToFill.buffer->applyGain(0, bufferToFill.startSample, bufferToFill.startSample + bufferToFill.numSamples, leftGain);
        bufferToFill.buffer->applyGain(1, bufferToFill.startSample, bufferToFill.startSample + bufferToFill.numSamples, rightGain);

        // TODO tracks/buses
    }
}
