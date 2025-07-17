// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
