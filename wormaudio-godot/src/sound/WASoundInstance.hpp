// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <event/EventInstance.hpp>
#include <godot_cpp/classes/ref.hpp>

namespace wa
{
    class WASoundInstance : public godot::RefCounted
    {
        GDCLASS(WASoundInstance, RefCounted)

    public:
        explicit WASoundInstance(event::EventInstance::Ptr instance_);

        void markFreed() const;
        bool canFree() const;

        void setState(int state) const;

        void setPosition(godot::Vector3 position_) const;

    protected:
        static void _bind_methods();

        WASoundInstance() = default;

        event::EventInstance::Ptr instance;
    };
}