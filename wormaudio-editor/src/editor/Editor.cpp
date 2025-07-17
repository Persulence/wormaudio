// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "Editor.hpp"

#include <runtime/Runtime.hpp>

#include "asset/AssetManager.hpp"

namespace editor
{
    using namespace resource;

    Editor::Editor()
    {
        // project = resource::make<Project>(std::make_unique<asset::AssetManager>(true));

        // TODO: remove, this will be done manually
        // const auto event = project->addEvent(event::EventDef::create());

        globalParameters = std::make_unique<EditorParameterList>(resource::make<event::ParameterListImpl>());
        // setCurrentEvent(event);

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

    void Editor::setCurrentEvent(const Handle<event::EventDef> &event, bool notify)
    {
        this->event = event;

        refreshParameters();

        // Allow the previous instance to be deleted
        if (instance && instance->getParent() != this->event)
            instance->markFreed();

        if (!instance || instance->getParent() != this->event)
            instance = std::make_shared<EditorEventInstance>(event);

        if (notify)
        {
            onEventChanged.emit();
        }
    }

    void Editor::startRuntime()
    {
        runtime = std::make_unique<runtime::Runtime>();
        lifecycleChanged.emit(0);
    }

    asset::AssetHandle Editor::createAsset(juce::File file)
    {
        asset::LocalPath localPath = asset::AssetLoader::getInstance()->localise(file.getFullPathName().toStdString());
        return project->getAssetManager().get(localPath);
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
                juce::MessageManager::callAsync([this]
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

    bool Editor::isPlaying() const
    {
        return runtime->transport.getState() == player::PLAYING;
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

    void Editor::setProject(Handle<Project> project_)
    {
        // Set the asset loader's root path (jank)
        asset::AssetLoader::getInstance()->setAssetRoot(saveManager.getAssetsFolder());

        // Set up the project (also jank)
        project = std::move(project_);

        project->assetManager->preprocess();

        if (runtime)
            runtime->getParameters().refresh(*project->globalParameters);

        if (!project->events.empty())
            setCurrentEvent(project->events.at(0), false);
        else
            setCurrentEvent(project->addEvent(event::EventDef::create()), false);

        onProjectRefreshed.emit();

        globalParameters->setTarget(project->globalParameters);

    }

    void Editor::eraseElement(const Handle<element::Element> &handle) const
    {
        for (auto& state : event->getDefinition()->getStates())
        {
            state->removeElement(handle);
        }

        event->getElements().unReg(handle);
    }
}
