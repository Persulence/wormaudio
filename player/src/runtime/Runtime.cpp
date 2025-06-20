#include "Runtime.hpp"

namespace runtime
{
    Runtime::Runtime()
    {
        listen(transport.signal, [this](auto state)
        {
            switch (state)
            {
                case player::STARTING:
                    break;
                case player::PLAYING:
                    logicTicker->start();
                    break;
                case player::STOPPING:
                    break;
                case player::STOPPED:
                    logicTicker->stop();
                    break;
                default: ;
            }
        });
    }

    event::EventInstance::Ptr Runtime::instantiate(const event::EventDef::Ptr &event)
    {
        auto instance = event->instantiate();
        instances.push_back(instance);
        return instance;
    }

    void Runtime::addInstance(const event::EventInstance::Ptr &instance)
    {
        instances.push_back(instance);
    }

    void Runtime::clearInstances()
    {
        for (auto& instance : instances)
        {
            instance->stop();
        }

        elementManager.clear();
        instances.clear();
    }

    void Runtime::connectToDevice()
    {
        start();
        if (logicTicker == nullptr)
        {
            logicTicker = std::make_unique<LogicTicker>();
            logicTicker->callback = [this]{ logicTick(); };
        }
    }

    void Runtime::disconnect()
    {
        logicTicker->stop();
        logicTicker = nullptr;

        stop();
    }

    // void Runtime::setupParameters(std::shared_ptr<event::ParameterList> list)
    // {
    //     parameters.refresh(list);
    // }

    sm::ParameterLookup & Runtime::getParameters()
    {
        return parameters;
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
        if (transport.stopped())
        {
            bufferToFill.clearActiveBufferRegion();
            return;
        }

        elementManager.getNextAudioBlock(bufferToFill);
    }

    void Runtime::logicTick()
    {
        for (const auto& instance : instances)
        {
            instance->logicTick(parameters, elementManager, transport);
        }

        // TODO: make this async
        elementManager.freeReleased();
    }
}
