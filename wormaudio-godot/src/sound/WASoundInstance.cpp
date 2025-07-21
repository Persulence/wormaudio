// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "WASoundInstance.hpp"

#include "sound/WATransport.hpp"

namespace wa
{
    WASoundInstance::WASoundInstance(event::EventInstance::Ptr instance_):
        instance(std::move(instance_))
    {

    }

    void WASoundInstance::markFreed() const
    {
        instance->markFreed();
    }

    bool WASoundInstance::canFree() const
    {
        return instance->canFree();
    }

    void WASoundInstance::setState(int state) const
    {
        instance->transport.setState(static_cast<player::TransportState>(state));
    }

    void WASoundInstance::setPosition(godot::Vector3 position_) const
    {
        instance->setPosition({position_.x, position_.y, position_.z});
    }

    void WASoundInstance::_bind_methods()
    {
        using namespace godot;

        ClassDB::bind_method(D_METHOD("mark_done"), &WASoundInstance::markFreed);
        ClassDB::bind_method(D_METHOD("can_free"), &WASoundInstance::canFree);
        ClassDB::bind_method(D_METHOD("set_state", "transport_state"), &WASoundInstance::setState);
        ClassDB::bind_method(D_METHOD("set_position", "position"), &WASoundInstance::setPosition);
    }
}
