#pragma once

#include "bindings.h"
#include "runtime/Runtime.hpp"

namespace binding
{
    class NRuntime : WrapperBase
    {
    public:
        NRuntime();
        std::shared_ptr<event::EventInstance> instantiate(const binding::NEventDef &def) const;
        void startMessageManager() const;
        void stopMessageManager() const;
        void connectToDevice() const;
        void disconnect() const;

    private:
        std::unique_ptr<runtime::Runtime> backing;
    };
}
