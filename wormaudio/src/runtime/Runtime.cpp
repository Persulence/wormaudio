// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "Runtime.hpp"

#include "event/LogicTickInfo.hpp"

namespace runtime
{
    Runtime::Runtime()
    {
        collectFreeInstances.callback = [this]{ pruneInstances(); };

        listen(transport.signal, [this](auto state)
        {
            switch (state)
            {
                case player::STARTING:
                case player::PLAYING:
                    collectFreeInstances.startTimer(500);
                    break;
                case player::STOPPING:
                case player::STOPPED:
                    collectFreeInstances.stopTimer();
                    clearInstances();
                    break;
                default: ;
            }
        });
    }

    Runtime::~Runtime()
    {
        collectFreeInstances.stopTimer();
        disconnect();
    }

    event::EventInstance::Ptr Runtime::instantiate(const resource::Handle<event::EventDef> &event)
    {
        auto instance = event->instantiate();
        addInstance(instance);
        return instance;
    }

    void Runtime::addInstance(const event::EventInstance::Ptr &instance)
    {
        std::lock_guard lock{instancesMutex};
        instance->prepareToPlay(audioContext);
        instances.push_back(instance);
    }

    const std::vector<event::EventInstance::Ptr>& Runtime::getInstances()
    {
        return instances;
    }

    void Runtime::clearInstances()
    {
        std::lock_guard lock{instancesMutex};
        for (auto& instance : instances)
        {
            instance->stopInternal();
        }

        instances.clear();
    }

    void Runtime::pruneInstances()
    {
        std::lock_guard lock{instancesMutex};
        std::erase_if(instances, [](auto& i){ return i->canFree(); });

        // juce::Logger::writeToLog("Current instance count after prune: " + std::to_string(instances.size()));
        // for (auto& i : instances)
        // {
        //     juce::Logger::writeToLog(std::format("canFree: {}", i->canFree()));
        // }
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
            std::lock_guard lock{instancesMutex};

            // auto logicFuture = std::async(std::launch::async, [this]{ logicTick(); });
            logicTick();

            for (const auto& event : instances)
            {
                auto& elements = event->getElements();
                elements.getNextAudioBlock(bufferToFill, listener);

                // Happens after sample generation to allow handoff
                // TODO: make this async
                elements.freeReleased();
            }

            // logicFuture.get();
        }

        samplesPast += audioContext.samplesPerBlock;
    }

    void Runtime::logicTick()
    {
        // player::Seconds blockBegin = static_cast<player::Seconds>(samplesPast * audioContext.sampleDuration);
        auto info = event::LogicTickInfo{audioContext, samplesPast};

        int i = 0;
        for (const auto& instance : instances)
        {
            instance->logicTick(parameters, transport, info);
            i++;
        }

    }
}
