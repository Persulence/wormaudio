#pragma once

#include "event/ElementHandle.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

import element;

// namespace element
// {
//     class Element;
// }

namespace ui
{
    class ElementRegion : public juce::Component
    {
        event::ElementHandle element;

    public:
        explicit ElementRegion(event::ElementHandle element_):
            element(std::move(element_))
        { }

        void mouseDown(const juce::MouseEvent &event) override;

        void paint(juce::Graphics &g) override;
    };
}
