#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    /**
     * Covers the entire window. Holds the content component, which should be smaller.
     * Paints a drop shadow around the content.
     */
    class FakeModalDialogue : public juce::Component
    {
    public:
        std::shared_ptr<juce::Component> content;

        explicit FakeModalDialogue(std::shared_ptr<juce::Component> content);
        void paint(juce::Graphics &g) override;
        void paintOverChildren(juce::Graphics &g) override;
        void resized() override;

    private:
        juce::DropShadow dropShadow;
    };
}
