#pragma once

#include "StateCanvasPanel.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    // class CanvasViewport : public juce::Viewport
    class CanvasViewport : public juce::Component

    {
    public:
        juce::ComponentDragger canvasDragger;
        StateCanvasPanel canvas;

        CanvasViewport();
        void resized() override;

        void mouseDown(const juce::MouseEvent &event) override;
        void mouseDrag(const juce::MouseEvent &event) override;
    };
}
