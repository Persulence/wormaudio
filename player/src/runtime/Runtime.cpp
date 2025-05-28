#include "Runtime.hpp"

namespace runtime
{
    Runtime::Runtime()
    {
    }

    event::EventInstance::Ptr Runtime::instantiate(const event::Event::Ptr &event)
    {
        auto instance = event->instantiate();
        instances.push_back(instance);
        return instance;
    }

    void Runtime::clearInstances()
    {
        for (auto& instance : instances)
        {
            instance->stop();
        }

        instances.clear();
    }

    void Runtime::connectToDevice()
    {
        start();
        if (logicTicker == nullptr)
        {
            logicTicker = std::make_unique<LogicTicker>();
            logicTicker->callback = [this]{ logicTick(); };
            logicTicker->start();
        }
    }

    void Runtime::disconnect()
    {
        logicTicker->stop();
        logicTicker = nullptr;

        stop();
    }

    void Runtime::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
        elementManager.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }

    void Runtime::releaseResources()
    {
        elementManager.releaseResources();
    }

    void Runtime::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
    {
        elementManager.getNextAudioBlock(bufferToFill);
    }

    void Runtime::logicTick()
    {
        for (const auto& instance : instances)
        {
            instance->logicTick(parameters, elementManager, transport);
        }
    }
}
