#include "ElementInstanceManager.hpp"

#include <juce_audio_basics/juce_audio_basics.h>

#include "instance/spatial.hpp"
#include "resource/ElementInstance.hpp"

namespace player
{
    ElementInstancePtr ElementInstanceManager::addInstance(const ElementInstancePtr& element)
    {
        // tODO: look into reusing identical instances
        std::lock_guard lock(activeMutex);
        // active.insert(element);
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

    void ElementInstanceManager::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
        audioContext = {samplesPerBlockExpected, sampleRate};

        // TODO: channels
        accumulator = juce::AudioSampleBuffer(2, samplesPerBlockExpected);
    }

    void ElementInstanceManager::releaseResources()
    {
        audioContext = {};
    }

    void ElementInstanceManager::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
    {
        if (stagedHandoff != NULL_SAMPLE)
        {
            std::lock_guard lock(activeMutex);

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
            std::lock_guard lock(activeMutex); // Prevent the iterator from being invalidated
            for (auto& instance : active)
            {
                instance->getNextAudioBlock(bufferToFill);
            }
        }


        // TODO: TESTING ONLY
        // // auto soundPos = instance::Vec3f{1, 0, 0}; // South, so left channel
        // auto soundPos = instance::Vec3f{0, 0, 0};
        // auto listener = instance::Vec3f{0, 0, 0};
        //
        // float result = earDistance(soundPos, listener, 0);
        // float theta = (result + 1.f) * std::numbers::pi / 4;
        //
        // // float leftGain = result < 0 ? std::max(0.f, result + 1) : 0;
        // // float rightGain = result > 0 ? std::max(0.f, 1 - result) : 0;
        // float leftGain = std::cos(theta);
        // float rightGain = std::sin(theta);
        // bufferToFill.buffer->applyGain(0, bufferToFill.startSample, bufferToFill.startSample + bufferToFill.numSamples, leftGain);
        // bufferToFill.buffer->applyGain(1, bufferToFill.startSample, bufferToFill.startSample + bufferToFill.numSamples, rightGain);

        // TODO tracks/buses
    }
}
