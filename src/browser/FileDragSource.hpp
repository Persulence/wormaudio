#pragma once

#include "juce_core/juce_core.h"

namespace ui
{
    class FileDragSource
    {
    public:
        virtual ~FileDragSource() = default;

        virtual juce::File getFile() = 0;
    };
}