// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <godot_cpp/classes/object.hpp>
#include <state/Parameter.hpp>

namespace wa
{
    class WASoundDef;
    class WASoundInstance;
}

namespace wa
{
    /// Utility class for accessing the runtime via GDScript.
    class WARuntime : public godot::Object
    {
        GDCLASS(WARuntime, Object)

    public:
        static ParameterValue getParamVal(godot::String name);
        static void setParamVal(godot::String name, ParameterValue value);
        static WASoundInstance* instantiate(const WASoundDef* def);

    protected:
        static void _bind_methods();
    };
}
