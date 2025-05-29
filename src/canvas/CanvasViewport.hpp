#pragma once

#include "StateCanvasPanel.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class CanvasViewport : public juce::Viewport
    {
    public:
        StateCanvasPanel canvas;

        CanvasViewport();
        void resized() override;
    };
}
