// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "WATransport.hpp"

#include <godot_cpp/core/class_db.hpp>

namespace wa
{
    void WATransport::_bind_methods()
    {
        using namespace godot;
        using namespace player;

        BIND_CONSTANT(STARTING);
        BIND_CONSTANT(PLAYING);
        BIND_CONSTANT(STOPPING);
        BIND_CONSTANT(STOPPED);
    }
}

