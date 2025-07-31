// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "runtime.b.hpp"

namespace binding
{
    WARuntime::WARuntime()
    {
        backing = std::make_unique<runtime::Runtime>();
    }

    std::shared_ptr<event::EventInstance> WARuntime::instantiate(const WASoundDef &def) const
    {
        return backing->instantiate(def.eventDef);
    }

    void WARuntime::connectToDevice() const
    {
        backing->connectToDevice();
    }

    void WARuntime::disconnect() const
    {
        backing->disconnect();
    }

    void WARuntime::setListenerPosition(double x, double y, double z) const
    {
        backing->setListenerPosition(instance::Vec3f{x, y, z});
    }

    void WARuntime::setListenerYaw(float yaw) const
    {
        backing->setListenerYaw(yaw);
    }

    void WARuntime::clearInstances() const
    {
        backing->clearInstances();
    }

    int WARuntime::getInstanceCount() const
    {
        return backing->getInstances().size();
    }

    void WARuntime::setState(player::TransportState state) const
    {
        backing->transport.setState(state);
    }
}

