
#include "EditorEventInstance.hpp"

namespace editor
{
    using namespace event;

    EditorEventInstance::EditorEventInstance(Event::Ptr parent_):
        EventInstance(parent_)
    {

    }

    void EditorEventInstance::refresh()
    {
        stateManager = {StateMachineInstance(parent->getDefinition()->getStates(), parent->getDefinition()->getStart())};
    }
}
