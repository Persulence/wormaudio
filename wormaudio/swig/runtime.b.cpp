// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "runtime.b.hpp"

namespace binding
{
    NRuntime::NRuntime()
    {
        backing = std::make_unique<runtime::Runtime>();
    }

    std::shared_ptr<event::EventInstance> NRuntime::instantiate(const NEventDef &def) const
    {
        return backing->instantiate(def.eventDef);
    }

    void NRuntime::connectToDevice() const
    {
        backing->connectToDevice();
    }

    void NRuntime::disconnect() const
    {
        backing->disconnect();
    }

    void NRuntime::setState(player::TransportState state) const
    {
        backing->transport.setState(state);
    }
}

