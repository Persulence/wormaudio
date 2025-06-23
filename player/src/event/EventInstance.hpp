#pragma once

#include <memory>
#include <utility>

#include "AutomationTableInstance.hpp"
#include "EventElementInstancer.hpp"

#include "EventDef.hpp"
#include "LogicTickInfo.hpp"
#include "StateMachineInstance.hpp"
#include "player/transport.hpp"

namespace event
{
    class EventInstance
    {
    protected:
        resource::Handle<EventDef> parent;
        StateMachineInstance stateManager;

    public:
        using Ptr = std::shared_ptr<EventInstance>;

        player::TransportControl transport;

        std::unique_ptr<automation::AutomationTableInstance> automationInstance;

        explicit EventInstance(resource::Handle<EventDef> parent_):
            parent(std::move(parent_)),
            stateManager(StateMachineInstance(parent->getDefinition()->getStates(), parent->getDefinition()->getStart())),
            automationInstance(std::make_unique<automation::AutomationTableInstance>(parent->getAutomation()))
        {}

        void logicTick(sm::ParameterLookup &parameters, player::ElementInstanceManager& context, player::TransportControl& globalTransport,
            const LogicTickInfo& info)
        {
            if (transport.getState() == player::STARTING)
            {
                // Starting on the block
                parameters.resetStateTimer(info.blockBeginSamples);
                transport.setState(player::PLAYING);
            }

            if (transport.getState() == player::PLAYING)
            {
                EventElementInstancer instancer{context, *automationInstance};
                automationInstance->logicTick(parameters, transport);
                stateManager.logicTick(parameters, instancer, transport, info);
            }
            else
            {
                return;
            }

            if (transport.stopped())
            {
                stop();
            }
        }

        void stop() const
        {
            stateManager.stop();
        }
    };
}

