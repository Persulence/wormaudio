#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class FileDragSource
    {
    public:
        static FileDragSource* test(const juce::DragAndDropTarget::SourceDetails &details)
        {
            return dynamic_cast<FileDragSource*>(details.sourceComponent.get());
        }

        virtual juce::File getFile() = 0;

        virtual ~FileDragSource() = default;
    };
}