// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

        void prepareToPlay(player::AudioContext ctx);

        void logicTick(sm::GlobalParameterLookup& globalParameters, player::TransportControl& globalTransport,
                       const LogicTickInfo& info);

        void setState(player::TransportState state);

        void stopInternal() const;

        void setPosition(const instance::Vec3f position_) { position = position_; }

        player::ElementInstanceManager& getElements();
        void setVelocity(const instance::Vec3f velocity_) { velocity = velocity_; }

    protected:
        resource::Handle<EventDef> parent;
        std::unique_ptr<automation::AutomationTableInstance> automationInstance;
        StateMachineInstance stateManager;
        std::unique_ptr<player::ElementInstanceManager> elementManager;

        instance::Vec3f position;
        instance::Vec3f velocity;

    private:
        sm::EventParameterLookup parameters;
    };
}