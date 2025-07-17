// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
