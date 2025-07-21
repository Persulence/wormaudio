
// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <godot_cpp/core/binder_common.hpp>
#include <player/transport.hpp>

#include "godot_cpp/variant/variant.hpp"

namespace wa
{
    class WATransport : public godot::Object
    {
        GDCLASS(WATransport, Object)

    protected:
        static void _bind_methods();

    };
}

VARIANT_ENUM_CAST(player::TransportState);
