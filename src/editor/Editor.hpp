#pragma once

#include <cassert>
#include <runtime/Runtime.hpp>

#include "control/StateMachineDefinition.hpp"
#include "signal/Signal.hpp"

import event;
import transport;

namespace editor
{
    class Editor : player::TransportCallback::Listener
    {
        event::Event::Ptr event;
        std::unique_ptr<runtime::Runtime> runtime;

        // TODO: using a single, hardcoded event for testing
        Editor():
            event(event::Event::create())
        {
        }

    public:
        player::TransportCallback::Signal transportSignal;

        static Editor& getInstance()
        {
            static Editor instance;
            return instance;
        }

        [[nodiscard]] runtime::Runtime& getRuntime() const
        {
            assert(runtime != nullptr);
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

        [[nodiscard]] std::shared_ptr<sm::StateMachineDefinition> getDefinition() const
        {
            return event->getDefinition();
        }

        void play()
        {
            auto& runtime = getRuntime();
            transportSignal.emit(player::PLAYING);
            auto instance = runtime.instantiate(event);

            listen(instance->transport.signal, [this](auto state)
            {
                setState(state, true);
            });

            instance->transport.setState(player::PLAYING);

            runtime.transport.setState(player::PLAYING);
        }

        void setState(player::TransportState state, bool notify)
        {
            switch (state)
            {
                case player::STOPPING:
                    break;
                case player::STOPPED:
                    getRuntime().clearInstances();
                    getRuntime().transport.setState(player::STOPPED);
                    break;
                case player::STARTING:
                    // TODO
                    break;
                case player::PLAYING:
                    // TODO
                    break;
            }
            if (notify)
                transportSignal.emit(state);
        }

        void stop()
        {
            setState(player::STOPPED, true);
        }

        void shutdown()
        {
            if (runtime)
            {
                stop();
                runtime->disconnect();
                runtime = nullptr;
            }

            event = nullptr;
        }
    };
}