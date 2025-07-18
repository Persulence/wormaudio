// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "EventInstance.hpp"

namespace event
{
    EventInstance::EventInstance(resource::Handle<EventDef> parent_):
        parent(std::move(parent_)),
        automationInstance(std::make_unique<automation::AutomationTableInstance>(parent->getAutomation())),
        stateManager(StateMachineInstance(parent->getDefinition()->getStates(), parent->getDefinition()->getStart())),
        elementManager(std::make_unique<player::ElementInstanceManager>(position, parent->getProperties()))
    {
        transport.signal.setup(&transportListener, [this](auto state)
        {
            if (state == player::STARTING)
            {
                stateManager.restart();
            }

            if (state == player::STOPPING)
            {
                transport.setState(player::STOPPED);
                stopInternal();
            }
        });
    }

    void EventInstance::prepareToPlay(player::AudioContext ctx) const
    {
        elementManager->prepareToPlay({ctx.samplesPerBlock, ctx.sampleRate});
    }

    void EventInstance::logicTick(sm::GlobalParameterLookup &globalParameters,
                                  player::TransportControl &globalTransport, const LogicTickInfo &info)
    {
        // This can't be a good idea
        parameters.setParent(&globalParameters);

        if (transport.getState() == player::STARTING)
        {
            // Starting on the block
            parameters.resetStateTimer(info.blockBeginSamples);
            transport.setState(player::PLAYING);
        }

        if (transport.getState() == player::PLAYING)
        {
            EventElementInstancer instancer{*elementManager, *automationInstance};
            automationInstance->logicTick(parameters, transport);
            stateManager.logicTick(parameters, instancer, transport, info);
        }
        else
        {
            return;
        }

        if (transport.stopped())
        {
            stopInternal();
        }
    }

    bool EventInstance::canFree() const
    {
        return freed && transport.stopped();
    }

    void EventInstance::markFreed()
    {
        freed = true;
        juce::Logger::writeToLog("Freed");
    }

    void EventInstance::stopInternal() const
    {
        stateManager.stop();
        elementManager->clear();
    }

    player::ElementInstanceManager &EventInstance::getElements() const
    {
        return *elementManager;
    }
}
