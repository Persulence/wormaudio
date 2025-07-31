// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
