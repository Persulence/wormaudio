#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class OutlineItemComponent : public juce::Component
    {
    public:
        explicit OutlineItemComponent(const std::string &icon, bool editable = true);
        OutlineItemComponent();

        void paint(juce::Graphics &g) override;
        void resized() override;

    public:
        juce::Label label;
        juce::Image icon;

    private:
        juce::Rectangle<int> iconBounds;
    };
}
