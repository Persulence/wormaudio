#pragma once

#include <cassert>
#include <runtime/Runtime.hpp>

#include "control/StateMachineDefinition.hpp"
#include "signal/Signal.hpp"

import event;
import transport;

namespace editor
{
    using TransportCallback = signal_event::Callback<player::TransportState>;

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
        TransportCallback::Signal transportSignal;

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

        void play()
        {
            transportSignal.emit(player::PLAYING);
            getRuntime().instantiate(event);
        }

        void stop()
        {
            transportSignal.emit(player::STOPPED);
            getRuntime().clearInstances();
        }
    };
}