// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "player/ElementInstanceManager.hpp"
#include "resource/Element.hpp"
#include "resource/ElementInstance.hpp"
#include "resource/ElementInstanceContext.hpp"

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

        void stageHandoff(player::Sample sample) override
        {
            manager.stageHandoff(sample);
        }

    private:
        player::ElementInstanceManager& manager;
        automation::AutomationRegistryInstance& automation;
    };
}
