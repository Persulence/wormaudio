#include "Runtime.hpp"

#include "event/LogicTickInfo.hpp"

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
                    break;
                case player::STOPPING:
                    break;
                case player::STOPPED:
                    break;
                default: ;
            }
        });
    }

    event::EventInstance::Ptr Runtime::instantiate(const resource::Handle<event::EventDef> &event)
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
    }

    void Runtime::disconnect()
    {
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
        audioContext = {samplesPerBlockExpected, sampleRate};
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
        }
        else
        {
            // TODO: look into making this async
            logicTick();

            elementManager.getNextAudioBlock(bufferToFill);

            // Happens after sample generation to allow handoff
            // TODO: make this async
            // elementManager.freeReleased();
        }

        samplesPast += audioContext.samplesPerBlock;
    }

    void Runtime::logicTick()
    {
        // player::Seconds blockBegin = static_cast<player::Seconds>(samplesPast * audioContext.sampleDuration);
        auto info = event::LogicTickInfo{audioContext, samplesPast};
        for (const auto& instance : instances)
        {
            instance->logicTick(parameters, elementManager, transport, info);
        }

    }
}
