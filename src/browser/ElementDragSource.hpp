#pragma once

#include "event/ElementHandle.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class ElementDragSource
    {
    public:
        static bool test(const juce::DragAndDropTarget::SourceDetails &details)
        {
            return dynamic_cast<ElementDragSource*>(details.sourceComponent.get());
        }

        virtual event::ElementHandle getHandle() = 0;

        virtual ~ElementDragSource() = default;
    };
}
