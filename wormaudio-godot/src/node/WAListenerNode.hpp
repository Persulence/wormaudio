// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <numbers>
#include <godot_cpp/classes/node3d.hpp>

namespace wa
{
    class WAListenerNode : public godot::Node3D
    {
        GDCLASS(WAListenerNode, Node3D)
    public:

    protected:
        void physicsProcess(double delta) const;
        void ready();

        void _notification(int id);
        static void _bind_methods();
    };
}

