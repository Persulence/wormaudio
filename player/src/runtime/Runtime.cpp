// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

    Runtime::~Runtime()
    {
    }

    event::EventInstance::Ptr Runtime::instantiate(const resource::Handle<event::EventDef> &event)
    {
        auto instance = event->instantiate();
        instances.push_back(instance);
        instance->prepareToPlay(audioContext);
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
            instance->stopInternal();
        }

        instances.clear();
    }

    void Runtime::pruneInstances()
    {
        for (auto& instance : instances)
        {
            // instance->
        }
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

    sm::GlobalParameterLookup &Runtime::getParameters()
    {
        return parameters;
    }

    void Runtime::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
        audioContext = {samplesPerBlockExpected, sampleRate};
    }

    void Runtime::releaseResources()
    {
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

            for (auto& event : instances)
            {
                auto& elements = event->getElements();
                elements.getNextAudioBlock(bufferToFill);

                // Happens after sample generation to allow handoff
                // TODO: make this async
                elements.freeReleased();
            }
        }

        samplesPast += audioContext.samplesPerBlock;
    }

    void Runtime::logicTick()
    {
        // player::Seconds blockBegin = static_cast<player::Seconds>(samplesPast * audioContext.sampleDuration);
        auto info = event::LogicTickInfo{audioContext, samplesPast};
        for (const auto& instance : instances)
        {
            instance->logicTick(parameters, transport, info);
        }

    }
}
