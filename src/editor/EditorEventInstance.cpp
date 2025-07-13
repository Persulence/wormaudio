
// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "EditorEventInstance.hpp"

#include <utility>

#include "event/AutomationTableInstance.hpp"

namespace editor
{
    using namespace event;

    EditorEventInstance::EditorEventInstance(resource::Handle<EventDef> parent_):
        EventInstance(std::move(parent_))
    {

    }

    void EditorEventInstance::refresh()
    {
        stateManager = {StateMachineInstance(parent->getDefinition()->getStates(), parent->getDefinition()->getStart())};

        automationInstance = std::make_unique<automation::AutomationTableInstance>(parent->getAutomation());
    }
}
