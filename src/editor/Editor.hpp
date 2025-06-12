#pragma once

#include <cassert>
#include <runtime/Runtime.hpp>

#include "juce_gui_basics/juce_gui_basics.h"

#include "EditorEventInstance.hpp"
#include "EditorParameterList.hpp"
#include "state/StateMachineDefinition.hpp"

import event;
import transport;

namespace editor
{
    using EventChanged = signal_event::Callback<>;
    using Lifecycle = signal_event::Callback<int>;
    using ParametersChanged = signal_event::Callback<>;

    class Editor :
        player::TransportCallback::Listener,
        EditorParameterList::Changed::Listener
    {
        std::unique_ptr<runtime::Runtime> runtime;

        event::Event::Ptr event;
        EditorEventInstance::Ptr instance;
        EditorParameterList globalParameters;

        // TODO: using a single, hardcoded event for testing
        Editor():
            event(event::Event::create())
        {
            loadEvent(event);

            globalParameters.changed.setup(this, [this](){ refreshParameters(); });
            // EditorParameterList::Changed::Listener::listen(globalParameters.changed, [this](){ refreshParameters(); });

            // quit.setInfo("Quit", "Quit the application", "app", 0);
            // commands.registerCommand(quit);
            // commands.registerAllCommandsForTarget()

            // commands.invokeDirectly(quit.commandID, false);
        }

        void refreshParameters()
        {
            // Set up global parameters
            if (runtime)
                runtime->getParameters().refresh(globalParameters);

            parametersChanged.emit();
        }

        void loadEvent(const event::Event::Ptr& event)
        {
            refreshParameters();
            instance = std::make_shared<EditorEventInstance>(event);
        }

    public:
        player::TransportCallback::Signal transportSignal;
        EventChanged::Signal eventChanged;

        Lifecycle::Signal lifecycleChanged;
        ParametersChanged::Signal parametersChanged;

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

        void startRuntime()
        {
            runtime = std::make_unique<runtime::Runtime>();
            lifecycleChanged.emit(0);
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
            // Rebuild the instance's state machine
            instance->refresh();

            auto& runtime = getRuntime();
            transportSignal.emit(player::PLAYING);
            // auto instance = runtime.instantiate(event);
            runtime.addInstance(instance);

            instance->transport.signal.setup(this, [this](auto state)
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

            instance = nullptr;
            event = nullptr;
        }

        EditorParameterList& getGlobalParameters()
        {
            return globalParameters;
        }

    };

    // Saves a handful of characters
    inline Editor& getInstance()
    {
        return Editor::getInstance();
    }
}