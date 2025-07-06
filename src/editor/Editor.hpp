#pragma once

#include "Editor.fwd.hpp"

#include <cassert>
#include <filesystem>

#include "EditorEventInstance.hpp"
#include "EditorParameterList.hpp"
#include "ProjectSaveManager.hpp"
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

        void setCurrentEvent(const resource::Handle<event::EventDef>& event);

    public:
        DISABLE_COPY(Editor)
        DISABLE_MOVE(Editor)

        player::TransportCallback::Signal transportSignal;
        EventChanged::Signal eventChanged;

        Lifecycle::Signal lifecycleChanged;
        ParametersChanged::Signal parametersChanged;
        sm::OnStateChange::Signal onStateChange;
        ProjectRefreshed::Signal onProjectRefreshed;

        ProjectSaveManager saveManager;

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

        void startRuntime();

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
