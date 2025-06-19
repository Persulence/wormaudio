#pragma once

#include "resource/Element.hpp"
#include "resource/ElementInstance.hpp"
#include "resource/ElementInstanceContext.hpp"

import ElementInstanceManager;

namespace event
{
    class EventElementInstancer : public element::ElementInstanceContext
    {
    public:
        explicit EventElementInstancer(player::ElementInstanceManager& manager_, automation::AutomationRegistryInstance& automation_):
            manager(manager_),
            automation(automation_)
        {

        }

        element::ElementInstancePtr createInstance(element::Element &element) override
        {
            auto instance = element.createInstance(manager.getAudioContext(), automation);
            manager.addInstance(instance);
            return instance;
        }

    private:
        player::ElementInstanceManager& manager;
        automation::AutomationRegistryInstance& automation;
    };
}
