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
        static void startMessageManager();
        static void stopMessageManager();
        void connectToDevice() const;
        void disconnect() const;

    private:
        std::unique_ptr<runtime::Runtime> backing;
    };
}
