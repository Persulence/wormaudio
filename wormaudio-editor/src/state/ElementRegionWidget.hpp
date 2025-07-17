// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "event/ElementHandle.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class ElementRegionWidget : public juce::Component
    {
    public:
        explicit ElementRegionWidget(event::ElementHandle element_):
            element(std::move(element_))
        {
            refresh();
        }

        void mouseDown(const juce::MouseEvent &event) override;
        void paint(juce::Graphics &g) override;
        void resized() override;

        void refresh();

    private:
        event::ElementHandle element;
        std::unique_ptr<Component> impl;
    };
}
