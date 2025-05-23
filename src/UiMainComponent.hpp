#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Panel.hpp"
#include "canvas/StateCanvasPanel.hpp"

namespace ui
{
    // Split into file browser and element browser
    class LeftPanel : public Panel
    {
    public:
        LeftPanel();

    protected:
        void paint(juce::Graphics &g) override;
    };
    class UiMainComponent : public juce::Component
    {
        LeftPanel leftPanel;
        CentrePanel centrePanel;

        juce::TextButton b1;
        juce::TextButton b2;

    public:
        UiMainComponent();

        void resized() override;
    };
}
