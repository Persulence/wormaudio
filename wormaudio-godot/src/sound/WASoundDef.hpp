// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <event/EventDef.hpp>
#include <godot_cpp/classes/ref.hpp>

namespace wa
{
    class WASoundDef : public godot::RefCounted
    {
        GDCLASS(WASoundDef, RefCounted)

    public:
        explicit WASoundDef(std::shared_ptr<event::EventDef> def_);

        resource::Handle<event::EventDef> getBacking() const { return def; }

    protected:
        static void _bind_methods();

    private:
        resource::Handle<event::EventDef> def;

        WASoundDef() = default;

    };
}