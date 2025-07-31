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

#include "BaseElementWidget.hpp"

#include "canvas/InspectorSelectionManager.hpp"
#include "inspector/InspectorRoot.hpp"
#include "inspector/filler/ElementInspectorFiller.hpp"

namespace ui
{
    BaseElementWidget::BaseElementWidget(event::ElementHandle handle):
        handle(std::move(handle))
    {

    }

    void BaseElementWidget::mouseDown(const juce::MouseEvent &event)
    {
        if (const auto manager = findParentComponentOfClass<InspectorSelectionManager>())
        {
            manager->select(shared_from_this());
        }
    }

    std::shared_ptr<juce::Component> BaseElementWidget::createConfig()
    {
        return InspectorRoot::wrap(std::make_unique<ElementInspectorFiller>(handle));
    }
}
