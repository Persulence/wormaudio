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

    void NRuntime::startMessageManager()
    {
        runtime::Runtime::startMessageManager();
    }

    void NRuntime::stopMessageManager()
    {
        runtime::Runtime::stopMessageManager();
    }

    void NRuntime::connectToDevice() const
    {
        backing->connectToDevice();
    }

    void NRuntime::disconnect() const
    {
        backing->disconnect();
    }
}

