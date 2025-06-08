#pragma once

#include "automation/AutomationInstance.hpp"

import element;
import ElementInstance;
import ElementInstanceManager;

namespace event
{
    class EventElementInstancer : public element::ElementInstanceContext
    {
    public:
        explicit EventElementInstancer(player::ElementInstanceManager& manager_, automation::AutomationInstance& automation_):
            manager(manager_),
            automation(automation_)
        {

        }

        element::ElementInstancePtr createInstance(element::Element &element) override
        {
            return element.createInstance(manager.getAudioContext(), automation);
        }

    private:
        player::ElementInstanceManager& manager;
        automation::AutomationInstance& automation;
    };
}
