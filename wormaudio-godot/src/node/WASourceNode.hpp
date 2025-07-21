// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
