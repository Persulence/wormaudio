
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

#include "WARuntime.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <state/Parameter.hpp>

#include "WormAudioGodot.hpp"
#include "sound/WASoundDef.hpp"
#include "sound/WASoundInstance.hpp"

namespace wa
{
    ParameterValue WARuntime::getParamVal(godot::String name)
    {
        return WormAudioGodot::getInstance().getRuntime().getParameters().getValue(toString(name));
    }

    void WARuntime::setParamVal(godot::String name, ParameterValue value)
    {
        if (auto instance = WormAudioGodot::getInstance().getRuntime().getParameters().getChecked(toString(name)))
        {
            instance->setValue(value);
        }
    }

    WASoundInstance* WARuntime::instantiate(const WASoundDef *def)
    {
        assert(def);
        return memnew(WASoundInstance{WormAudioGodot::getInstance().getRuntime().instantiate(def->getBacking())});
    }

    void WARuntime::_bind_methods()
    {
        using namespace godot;

        ClassDB::bind_static_method("WARuntime", D_METHOD("get_param_val", "name"), &WARuntime::getParamVal);
        ClassDB::bind_static_method("WARuntime", D_METHOD("set_param_val", "name", "value"), &WARuntime::setParamVal);

        ClassDB::bind_static_method("WARuntime", D_METHOD("instantiate", "sound_def"), &WARuntime::instantiate);
    }
}
