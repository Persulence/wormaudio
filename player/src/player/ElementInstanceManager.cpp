module;

#include <vector>
#include <juce_audio_basics/juce_audio_basics.h>

module ElementInstanceManager;

namespace player
{
    ElementInstancePtr ElementInstanceManager::createInstance(const Element &element)
    {
        // tODO: look into reusing identical instances
        std::lock_guard lock(activeMutex);
        return active.emplace_back(element.createInstance(audioContext));
    }

    void ElementInstanceManager::clear()
    {
        active.clear();
    }

    void ElementInstanceManager::freeReleased()
    {
        std::ranges::remove_if(active, [](auto& e){ return e->canBeFreed(); });
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
        std::lock_guard lock(activeMutex); // Prevent the iterator from being invalidated
        for (auto& instance : active)
        {
            instance->getNextAudioBlock(bufferToFill);
        }

        // TODO tracks/buses
    }
}
