#include "Editor.hpp"

#include <runtime/Runtime.hpp>

namespace editor
{
    Editor::Editor()
    {
        project = resource::make<resource::Project>();
        event = project->addEvent(event::EventDef::create());

        globalParameters = std::make_unique<EditorParameterList>(project->globalParameters);
        loadEvent(event);

        globalParameters->changed.setup(this, [this]() { refreshParameters(); });
    }

    Editor::~Editor()
    {

    }

    void Editor::refreshParameters()
    {
        // Set up global parameters
        if (runtime)
            runtime->getParameters().refresh(*project->globalParameters);

        parametersChanged.emit();
    }

    void Editor::loadEvent(const resource::Handle<event::EventDef> &event)
    {
        refreshParameters();
        instance = std::make_shared<EditorEventInstance>(event);
    }

    void Editor::startRuntime()
    {
        runtime = std::make_unique<runtime::Runtime>();
        lifecycleChanged.emit(0);
    }

    void Editor::play()
    {
        // Rebuild the instance's state machine
        instance->refresh();

        // Connect to the new state machine's event
        instance->getStateMachine().onStateChange.setup(&stateListener, [this](const auto& newState)
        {
            juce::MessageManager::callAsync([this, newState]
            {
                onStateChange.emit(newState);
            });
        });

        auto &runtime = getRuntime();
        transportSignal.emit(player::PLAYING);
        // auto instance = runtime.instantiate(event);
        runtime.addInstance(instance);

        instance->transport.signal.setup(this, [this](auto state)
        {
            setState(state, true);
        });

        instance->transport.setState(player::STARTING);

        runtime.transport.setState(player::PLAYING);
    }

    void Editor::setState(player::TransportState state, bool notify)
    {
        switch (state)
        {
            case player::STOPPING:
                break;
            case player::STOPPED:
                getRuntime().clearInstances();
                getRuntime().transport.setState(player::STOPPED);
                MessageManager::callAsync([this]
                {
                    onStateChange.emit(nullptr);
                });
                break;
            case player::STARTING:
                // TODO
                break;
            case player::PLAYING:
                // TODO
                break;
        }

        if (notify)
        {
            juce::MessageManagerLock lock;
            transportSignal.emit(state);
        }
    }

    void Editor::shutdown()
    {
        if (runtime)
        {
            stop();
            runtime->disconnect();
            runtime = nullptr;
        }

        project = nullptr;
        instance = nullptr;
        event = nullptr;
    }
}
