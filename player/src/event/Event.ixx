module;

#include <memory>

#include "ParameterList.hpp"
#include "juce_core/juce_core.h"
#include "../control/StateMachineDefinition.hpp"

export module event:Event;

import control;
import parameter;

namespace event
{
    export class EventInstance;

    export class Event : public juce::ReferenceCountedObject
    {
        sm::StateMachineDefinition::Ptr definition;
        ParameterList parameters;

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

        ParameterList& getParameters()
        {
            return parameters;
        }

        // Defined after EventInstance
        std::shared_ptr<EventInstance> instantiate();
    };
}