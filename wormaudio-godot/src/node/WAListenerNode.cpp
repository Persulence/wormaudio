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

#include "WAListenerNode.hpp"

#include <godot_cpp/classes/engine.hpp>

#include "../WormAudioGodot.hpp"

namespace wa
{
    void WAListenerNode::physicsProcess(double unused) const
    {
        auto& runtime = WormAudioGodot::getInstance().getRuntime();

        const float yaw = get_global_rotation().y;
        const auto position = get_global_position();
        runtime.setListenerPosition({position.x, position.y, position.z});
        runtime.setListenerYaw(yaw + static_cast<float>(std::numbers::pi));
    }

    void WAListenerNode::ready()
    {
        if (!godot::Engine::get_singleton()->is_editor_hint())
            set_physics_process(true);
    }

    void WAListenerNode::_notification(int id)
    {
        switch (id)
        {
            case NOTIFICATION_READY:
                ready();
                break;
            case NOTIFICATION_PHYSICS_PROCESS:
                physicsProcess(get_physics_process_delta_time());
                break;
            default:
                break;
        }
    }

    void WAListenerNode::_bind_methods()
    {
        using namespace godot;
    }
}
