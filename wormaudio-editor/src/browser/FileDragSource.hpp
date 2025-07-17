// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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