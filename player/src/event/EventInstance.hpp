#pragma once

#include <memory>

#include "AutomationTableInstance.hpp"
#include "EventElementInstancer.hpp"

#include "EventDef.hpp"
#include "LogicTickInfo.hpp"
#include "StateMachineInstance.hpp"
#include "instance/instance.hpp"
#include "player/transport.hpp"
#include "state/EventParameterLookup.hpp"

namespace event
{
    class EventInstance
    {
    public:
        using Ptr = std::shared_ptr<EventInstance>;

        player::TransportControl transport;

        explicit EventInstance(resource::Handle<EventDef> parent_);

        void logicTick(sm::GlobalParameterLookup& globalParameters, player::ElementInstanceManager& context, player::TransportControl& globalTransport,
                       const LogicTickInfo& info);

        void stop() const;

        void setPosition(const instance::Position position_) { position = position_; };
        void setVelocity(const instance::Velocity velocity_) { velocity = velocity_; }

    protected:
        resource::Handle<EventDef> parent;
        std::unique_ptr<automation::AutomationTableInstance> automationInstance;
        StateMachineInstance stateManager;

        instance::Position position;
        instance::Velocity velocity;

    private:
        sm::EventParameterLookup parameters;
    };
}