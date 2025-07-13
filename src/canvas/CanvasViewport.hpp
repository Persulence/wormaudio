// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "StateCanvasPanel.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    // class CanvasViewport : public juce::Viewport
    class CanvasViewport : public Panel

    {
    public:
        juce::ComponentDragger canvasDragger;
        StateCanvasPanel canvas;

        CanvasViewport();
        void resized() override;
        void paint(juce::Graphics &g) override;

        void mouseDown(const juce::MouseEvent &event) override;
        void mouseDrag(const juce::MouseEvent &event) override;
    };
}
