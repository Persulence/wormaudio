#pragma once

#include "control/StateMachineDefinition.hpp"

import event;

namespace editor
{
    class Editor
    {
        event::Event::Ptr event;

        // TODO: using a single, hardcoded event for testing
        Editor():
            event(event::Event::create())
        {

        }

    public:
        static Editor& getInstance()
        {
            static Editor instance;
            return instance;
        }

        event::Event::Ptr getEvent()
        {
            return event;
        }

        std::shared_ptr<sm::StateMachineDefinition> getDefinition() const
        {
            return event->getDefinition();
        }
    };
}