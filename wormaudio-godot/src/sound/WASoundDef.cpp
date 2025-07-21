// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "WASoundDef.hpp"

namespace wa
{
    WASoundDef::WASoundDef(std::shared_ptr<event::EventDef> def_):
        def(std::move(def_))
    {

    }

    void WASoundDef::_bind_methods()
    {
        using namespace godot;

    }
}
