// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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