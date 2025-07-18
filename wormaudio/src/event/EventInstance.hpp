// Copyright (c) 2025 Thomas Paley-Menzies
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
        DISABLE_COPY(EventInstance)
        DISABLE_MOVE(EventInstance)

    public:
        using Ptr = std::shared_ptr<EventInstance>;

        player::TransportControl transport;

        explicit EventInstance(resource::Handle<EventDef> parent_);

        const resource::Handle<EventDef>& getParent() { return parent; }

        void prepareToPlay(player::AudioContext ctx) const;

        void logicTick(sm::GlobalParameterLookup& globalParameters, player::TransportControl& globalTransport,
                       const LogicTickInfo& info);

        bool canFree() const;
        void markFreed();

        void stopInternal() const;

        player::ElementInstanceManager& getElements() const;

        void setPosition(const instance::Vec3f position_) { position = position_; }
        void setVelocity(const instance::Vec3f velocity_) { velocity = velocity_; }

    protected:
        resource::Handle<EventDef> parent;
        std::unique_ptr<automation::AutomationTableInstance> automationInstance;
        StateMachineInstance stateManager;
        std::unique_ptr<player::ElementInstanceManager> elementManager;
        player::TransportCallback::Listener transportListener;

        instance::Vec3f position;
        instance::Vec3f velocity;

        bool freed{false};

    private:
        sm::EventParameterLookup parameters;
    };
}