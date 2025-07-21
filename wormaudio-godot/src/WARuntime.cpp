
// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "WARuntime.hpp"

#include <godot_cpp/core/class_db.hpp>
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
