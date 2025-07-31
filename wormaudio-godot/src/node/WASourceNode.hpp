// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <event/EventDef.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <resource/SharedResource.hpp>

namespace wa {
    class WASystemNode;
}

namespace wa
{
    class WASourceNode : public godot::Node3D
    {
        GDCLASS(WASourceNode, Node3D)

    public:
        godot::String getEventName() { return eventName; };
        void setEventName(const godot::String &name) { eventName = name; };

        void startPlaying();
        void stopPlaying();

        void updateInstance();
        void findEventDef();

        void _notification(int id);

        void ready();
        void physicsProcess(double delta);

    protected:
        static void _bind_methods();

    private:
        godot::String eventName;

        WASystemNode* systemNodeCache;
        resource::Handle<event::EventDef> eventDef;

        WASystemNode* getSystemNode();

        std::shared_ptr<event::EventInstance> instance;
    };
}
