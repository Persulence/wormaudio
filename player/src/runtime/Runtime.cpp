#include "Runtime.hpp"

namespace runtime
{
    event::EventInstance::Ptr Runtime::instantiate(const event::Event::Ptr &event)
    {
        auto instance = event->instantiate();
        instances.push_back(instance);
        return instance;
    }

    Runtime::Runtime()
    {
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
        for (auto& instance : instances)
        {
            instance->logicTick(parameters, elementManager);
        }
    }
}
