
#include "EditorEventInstance.hpp"

#include <utility>

#include "event/AutomationTableInstance.hpp"

namespace editor
{
    using namespace event;

    EditorEventInstance::EditorEventInstance(EventDef::Ptr parent_):
        EventInstance(std::move(parent_))
    {

    }

    void EditorEventInstance::refresh()
    {
        stateManager = {StateMachineInstance(parent->getDefinition()->getStates(), parent->getDefinition()->getStart())};

        automationInstance = std::make_unique<automation::AutomationTableInstance>(parent->getAutomation());
    }
}
