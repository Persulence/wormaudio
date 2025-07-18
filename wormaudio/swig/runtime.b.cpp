// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

