#pragma once

#include <cassert>
#include <runtime/Runtime.hpp>

#include "control/StateMachineDefinition.hpp"

import event;

namespace editor
{
    class Editor
    {
        event::Event::Ptr event;
        std::unique_ptr<runtime::Runtime> runtime;

        // TODO: using a single, hardcoded event for testing
        Editor():
            event(event::Event::create())
        {
        }

    public:
        static Editor& getInstance()
        {
            static Editor instance;
            return instance;
        }

        runtime::Runtime& getRuntime() const
        {
            assert(runtime);
            return *runtime;
        }

        void setRuntime(std::unique_ptr<runtime::Runtime>&& runtime_)
        {
            runtime = std::move(runtime_);
        }

        event::Event::Ptr getEvent()
        {
            return event;
        }

        std::shared_ptr<sm::StateMachineDefinition> getDefinition() const
        {
            return event->getDefinition();
        }
    };
}