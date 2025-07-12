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

