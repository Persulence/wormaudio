// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
