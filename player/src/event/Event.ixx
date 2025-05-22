module;

#include <memory>

#include "juce_core/juce_core.h"

export module event:Event;

import control;

namespace event
{
    export class EventInstance;

    export class Event : public juce::ReferenceCountedObject
    {
        sm::StateMachineDefinition::Ptr definition;

        struct Private {};

    public:
        using Ptr = juce::ReferenceCountedObjectPtr<Event>;

        explicit Event(Private):
            definition(std::make_shared<sm::StateMachineDefinition>())
        {

        }

        static Ptr create()
        {
            return new Event(Private{});
        }

        const sm::StateMachineDefinition::Ptr& getDefinition()
        {
            return definition;
        }

        // Defined after EventInstance
        std::shared_ptr<EventInstance> instantiate();
    };
}