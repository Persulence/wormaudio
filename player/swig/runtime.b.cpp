#include "runtime.b.hpp"

namespace binding
{
    NRuntime::NRuntime(): backing(std::make_unique<runtime::Runtime>())
    {

    }

    std::shared_ptr<event::EventInstance> NRuntime::instantiate(const NEventDef &def) const
    {
        return backing->instantiate(def.eventDef);
    }

    void NRuntime::startMessageManager() const
    {
        backing->startMessageManager();
    }

    void NRuntime::stopMessageManager() const
    {
        backing->stopMessageManager();
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

