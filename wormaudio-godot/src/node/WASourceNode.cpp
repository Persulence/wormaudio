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

#include "WASourceNode.hpp"

#include <godot_cpp/classes/engine.hpp>

#include "WAListenerNode.hpp"
#include "WASystemNode.hpp"
#include "../WormAudioGodot.hpp"

namespace wa
{
    void WASourceNode::ready()
    {
        Node3D::_ready();
        systemNodeCache = nullptr;

        findEventDef();

        startPlaying();

        if (!godot::Engine::get_singleton()->is_editor_hint())
            set_physics_process(true);
    }

    void WASourceNode::physicsProcess(double delta)
    {
        if (instance)
        {
            if (auto parent = getSystemNode())
            {
                if (auto listener = parent->getListener())
                {
                    // auto difference = get_global_position() - listener->get_global_position();
                    // TODO: only set if dirty
                    const auto pos = get_global_position();
                    instance->setPosition({pos.x, pos.y, pos.z});
                }
            }
        }
    }

    void WASourceNode::startPlaying()
    {
        updateInstance();

        if (instance)
        {
            instance->transport.setState(player::STARTING);
        }
    }

    void WASourceNode::stopPlaying()
    {
        if (instance)
        {
            instance->transport.setState(player::STOPPING);
            instance->markFreed();
            instance = nullptr;
        }
    }

    void WASourceNode::updateInstance()
    {
        if (eventDef)
        {
            auto newInstance = WormAudioGodot::getInstance().getRuntime().instantiate(eventDef);
            if (instance && instance->getParent() != newInstance->getParent())
            {
                instance->markFreed();
                instance->transport.setState(player::STOPPED);
                instance = newInstance;
            }
            else if (!instance)
            {
                // Do not replace the instance when the parent has not changed.
                instance = newInstance;
            }
        }
        else
        {
            instance = nullptr;
        }
    }

    void WASourceNode::findEventDef()
    {
        if (!godot::Engine::get_singleton()->is_editor_hint())
        {
            if (auto node = getSystemNode())
            {
                if (const auto system = node->getSystem())
                {
                    auto path = toString(eventName.utf8().get_data());
                    eventDef = system->getEvent(eventName.utf8().get_data()).value_or(nullptr);

                    if (!eventDef)
                    {
                        WormAudioGodot::log(WormAudioGodot::ERROR, "Event not found " + path + "");
                    }
                }
                else
                {
                    WormAudioGodot::log(WormAudioGodot::ERROR, "System not loaded");
                }
            }
            else
            {
                WormAudioGodot::log("No WASystemNode found. Is one present and named %system?");
            }
        }
    }

    void WASourceNode::_notification(const int id)
    {
        switch (id)
        {
            case NOTIFICATION_PHYSICS_PROCESS:
                physicsProcess(0); // TODO: delta
                break;
            case NOTIFICATION_READY:
                ready();
            default:
                break;
        }
    }

    void WASourceNode::_bind_methods()
    {
        using namespace godot;
        ClassDB::bind_method(D_METHOD("set_event_name", "event_name"), &WASourceNode::setEventName);
        ClassDB::bind_method(D_METHOD("get_event_name"), &WASourceNode::getEventName);

        ADD_PROPERTY(PropertyInfo(Variant::STRING, "event_name", PROPERTY_HINT_NONE), "set_event_name",
                     "get_event_name");
    }

    template <typename T> T* findNodeInParents(godot::Node* node)
    {
        while (node)
        {
            if (auto found = dynamic_cast<T*>(node))
            {
                return found;
            }

            node = node->get_parent();
        }

        return nullptr;
    }

    WASystemNode* WASourceNode::getSystemNode()
    {
        if (!systemNodeCache)
        {
            if (const auto node = findNodeInParents<WASystemNode>(this))
            {
                systemNodeCache = node;
            }
        }

        return systemNodeCache;
    }
}
