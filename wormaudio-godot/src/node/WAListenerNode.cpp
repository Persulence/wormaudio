// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
