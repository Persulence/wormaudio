// Copyright (c)  2025 Persulence
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

#include "event/ElementHandle.hpp"
#include "juce_gui_basics/juce_gui_basics.h"
#include "util/selection/SelectionManager.hpp"

namespace ui
{
    class InspectorSelectionManager;

    class BaseElementWidget : public juce::Component, public SelectionTarget, public std::enable_shared_from_this<BaseElementWidget>
    {
    public:
        explicit BaseElementWidget(event::ElementHandle handle);
        void mouseDown(const juce::MouseEvent &event) override;

        std::shared_ptr<Component> createConfig() override;

    protected:
        event::ElementHandle handle;
    };
}
