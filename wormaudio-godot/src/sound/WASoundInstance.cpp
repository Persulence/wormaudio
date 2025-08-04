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

    int WASoundInstance::getState() const
    {
        return instance->transport.getState();
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
        ClassDB::bind_method(D_METHOD("get_state"), &WASoundInstance::getState);
        ClassDB::bind_method(D_METHOD("set_position", "position"), &WASoundInstance::setPosition);
    }
}
