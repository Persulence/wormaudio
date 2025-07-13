// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <memory>

#include "event/EventInstance.hpp"

namespace editor
{
    class EditorEventInstance : public event::EventInstance
    {
    public:
        using Ptr = std::shared_ptr<EditorEventInstance>;

        explicit EditorEventInstance(resource::Handle<event::EventDef> parent_);
        void refresh();

        event::StateMachineInstance& getStateMachine()
        {
            return stateManager;
        }

        resource::Handle<event::EventDef> getParent() { return parent; };
    };
}
