// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "Editor.hpp"

#include "juce_events/juce_events.h"

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
            juce::MessageManager::callAsync([this, state]
            {
                setState(state, true);
            });
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
        editorState.clear();
    }

    void Editor::setProject(Handle<Project> project_)
    {
        // editorState = EditorState{project}
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
            setCurrentEvent(project->addEvent(event::createEventDef()), false);

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

    void Editor::eraseEvent(const Handle<event::EventDef>& handle)
    {
        project->removeEvent(handle);

        if (!project->events.empty())
            setCurrentEvent(project->events.at(0), true);
        else
            setCurrentEvent(project->addEvent(event::createEventDef()), true);
    }

    void Editor::eraseGlobalParameter(const parameter::Parameter &parameter)
    {
        globalParameters->remove(parameter);
        // parametersChanged.emit();
    }
}
