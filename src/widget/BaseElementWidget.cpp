#include "BaseElementWidget.hpp"

#include "canvas/InspectorSelectionManager.hpp"
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
        return std::make_unique<ElementInspectorFiller>(handle);
    }
}
