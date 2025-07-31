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

