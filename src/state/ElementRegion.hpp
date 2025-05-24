#pragma once

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
        std::shared_ptr<element::Element> element;

    public:
        explicit ElementRegion(std::shared_ptr<element::Element> element_):
            element(std::move(element_))
        { }

        void paint(juce::Graphics &g) override;
    };
}
