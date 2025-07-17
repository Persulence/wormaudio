// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
