// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <memory>

#include "event/EventInstance.hpp"

namespace editor
{
    class EditorEventInstance : public event::EventInstance
    {
    public:
        using Ptr = std::shared_ptr<EditorEventInstance>;

        explicit EditorEventInstance(resource::Handle<event::EventDef> parent_);
        void refresh();

        event::StateMachineInstance& getStateMachine()
        {
            return stateManager;
        }

        resource::Handle<event::EventDef> getParent() { return parent; };
    };
}
