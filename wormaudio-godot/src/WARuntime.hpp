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
