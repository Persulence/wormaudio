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

        // This is a delegate to the current project's parameter list.
        // Use this variable when adding and removing parameters.
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

        void eraseEvent(const std::shared_ptr<event::EventDef> &handle);

        void eraseGlobalParameter(const parameter::Parameter& parameter);
    };

    // Saves a handful of characters
    inline Editor& getInstance()
    {
        return Editor::getInstance();
    }
}
