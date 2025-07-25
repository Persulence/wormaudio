// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "Editor.fwd.hpp"

#include <cassert>
#include <filesystem>

#include "EditorEventInstance.hpp"
#include "EditorParameterList.hpp"
#include "ProjectSaveManager.hpp"
#include "EditorState.hpp"

#include "event/EventDef.hpp"
#include "resource/Project.hpp"
#include "state/StateMachineDefinition.hpp"
#include "runtime/Runtime.fwd.hpp"

namespace editor
{
    class Editor :
        player::TransportCallback::Listener,
        EditorParameterList::Changed::Listener
    {
        std::unique_ptr<runtime::Runtime> runtime;

        resource::Handle<event::EventDef> event;

        resource::Handle<resource::Project> project;
        EditorEventInstance::Ptr instance;
        std::unique_ptr<EditorParameterList> globalParameters;
        sm::OnStateChange::Listener stateListener;

        Editor();
        ~Editor();

        void refreshParameters();

    public:
        DISABLE_COPY(Editor)
        DISABLE_MOVE(Editor)

        player::TransportCallback::Signal transportSignal;
        EventChanged::Signal eventChanged;

        Lifecycle::Signal lifecycleChanged;
        ParametersChanged::Signal parametersChanged;
        sm::OnStateChange::Signal onStateChange;
        ProjectRefreshed::Signal onProjectRefreshed;
        EventChanged::Signal onEventChanged;

        ProjectSaveManager saveManager;
        EditorState editorState;

        static Editor& getInstance()
        {
            static Editor instance;
            return instance;
        }

        EditorState& getState() { return editorState; };

        [[nodiscard]] runtime::Runtime& getRuntime() const
        {
            assert(runtime != nullptr);
            return *runtime;
        }

        void startRuntime();

        void setCurrentEvent(const resource::Handle<event::EventDef>& event, bool notify = false);

        resource::Handle<event::EventDef> getEvent()
        {
            return event;
        }

        decltype(instance)& getSoundInstance()
        {
            return instance;
        }

        [[nodiscard]] std::shared_ptr<sm::StateMachineDefinition> getDefinition() const
        {
            return event->getDefinition();
        }

        asset::AssetHandle createAsset(juce::File file);

        void play();
        void setState(player::TransportState state, bool notify);
        bool isPlaying() const;
        void stop() { setState(player::STOPPED, true); }

        void shutdown();

        EditorParameterList& getEditorParameters() const
        {
            return *globalParameters;
        }

        resource::Handle<resource::Project> getProject() const
        {
            return project;
        }

        void setProject(resource::Handle<resource::Project> project_);

        void eraseElement(const resource::Handle<element::Element> & handle) const;
    };

    // Saves a handful of characters
    inline Editor& getInstance()
    {
        return Editor::getInstance();
    }
}
